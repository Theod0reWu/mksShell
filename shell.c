#include "shell.h"
#define READ 0
#define WRITE 1

/*
char ** parse_args(char * line) ;
The line argument is what was typed into the shell.
It separates what was typed in at del (the delimiter) and puts each command into char ** args
returns char ** a, which is an array
*/
char ** parse_args(char * line, char * del) {
  char ** a = calloc(256, sizeof(char **)) ;
  int i ;
  char * q ;
  for (i = 0 ; (q = strsep(&line, del)) ; i++) {
    if (strcmp(q,"") != 0) {
      a[i] = q ;
    } else {
      i-- ;
    }
    //printf("|%s|\n",a[i] );
  }
  return a ;
}

/*
char ** parse_args_semicolon(char * line) ;
The line argument is what was typed into the shell.
It separates what was typed in at the semicolons and puts each command into char ** args
returns char ** a, which is the array of the command and any arguments it comes with
*/
char ** parse_args_semicolon(char * line) {
  return parse_args(line, ";") ;
}

/*
char ** parse_args(char * line) ;
The line argument are the seperate args without the semicolons
It seperates this command at the spaces and puts each part into char ** args
It also gets rid of spaces
returns char ** args, which is the array of the command and any arguments it comes with
 */
char ** parse_args_space(char * line) {
  return parse_args(line, " ") ;
}

/*
int is_redirect(char * line) ;
The argument is the line or command given.
It checks whether there will be redirecting or not.
Returns
*/
int is_redirect(char * line){
  return strchr(line, '<') != NULL || strchr(line, '>') != NULL;
}

/*
void pipe_it_up(char ** line) ;
It takes c as the argument so we check the user input given. We will use this to determine which commands we need to run.
It identifies the first and second commands, executes the first one if possible, and then uses the output from
the first command as the input to the second command that comes after the |.
It does not return anything, but it will print and get errno involved when there is something wrong with one or more of the commands.
*/
int pipe_it_up(char * comd) {
  char ** a = parse_args(comd, "|") ;
  char ** first = parse_args(a[0], " ") ; // this is the first command split on the spaces
  char ** second = parse_args(a[1], " ") ; // this is the second command split on the spaces
  if (execute(first) == -1 || execute(second) == -1) return -1 ;
  else {
    FILE * output = popen(a[0],"r") ;
    char * thing = malloc(256 * sizeof(char)) ;
    fgets(thing, 256, output) ;
    pclose(output) ;
    FILE * output2 = popen(a[1],"w") ;
    fprintf(output2, thing) ;
    pclose(output2) ;
    return 0 ;
  }
  /*char ** args = parse_args(c, "|") ;
  char ** first = parse_args(args[0], " ") ; // this is the first command we will execute
  char ** second = parse_args(args[1], " ") ; // the output of the first command is used as the input for this command
  int fd[2] ;
  int f = fork() ;
  if (!f) {
    if (pipe(fd) == -1) printf("Error with creating unnamed pipe: %s\n", strerror(errno)) ; ;
    f = fork() ;
    if (f) {
      close(fd[READ]) ;
      dup2(fd[WRITE], STDOUT_FILENO) ;
      if (execvp(first[0], first) == -1) printf("Error with piping regarding first commmand: %s/n", strerror(errno)) ;
    }
    else {
      wait(NULL) ;
      close(fd[WRITE]) ;
      dup2(fd[READ], STDIN_FILENO) ;
      if (execvp(second[0], second) == -1) printf("Error with piping regarding second commmand: %s/n", strerror(errno)) ;
    }
  }
  else {
    wait(NULL) ;
  }
  printf("");*/
}

/*
void redirecting(char ** args);
The argument is the redirection command with either > or < (but these are not as the first argument)
The next thing after the >,< should be the file name
This executes the command and returns 0 if it worked.
*/
int redirecting(char * line){
  int f;
  int copy;
  int worked = 0;
  char ** redir_parts;
  char ** args;
  char ** files;

  if (strchr(line,'<') != NULL && strchr(line,'>') != NULL) {
    //printf("detected double redirecting\n");
    char arg[256]; char outfile[256]; char infile[256];
    int i;
    for (i = 0; line[i] != '<' && line[i] != '>'; i++){
      arg[i] = line[i];
    }
    arg[i] = '\0';
    //printf("argument: %s\n", arg);
    args = parse_args(arg, " ");

    //printf("%s\n", line);

    i = 0;
    char * s = strchr(line, '<') + 1;
    while (*s != '\0' &&  *s != '>'){
     // printf("%s\n", s);
      if (*s != ' '){
        infile[i] = *s;
        ++i;
      }
      ++s;
    }
    infile[i] = '\0';

    //printf("%s\n", line);

    i = 0;
    s = strchr(line, '>') + 1;
    while (*s != '\0' &&  *s != '<'){
      //printf("%s\n", s);
      //printf("%i\n", s == NULL);
      if (*s != ' '){
        outfile[i] = *s;
        ++i;
      }
      ++s;
    }
    outfile[i] = '\0';

    //printf("|%s|\n", infile);
    //printf("|%s|\n", outfile);

    int copy1 = dup(fileno(stdin));
    int copy2 = dup(fileno(stdout));
    int f1 =  open(infile, O_RDONLY);
    int f2 =  open(outfile, O_WRONLY | O_CREAT, 0644);

    if (f1 < 0 || f2 < 0){
      printf("The system cannot find the file specified.\n");
      return 0;
    }

    dup2(f1, fileno(stdin));
    dup2(f2, fileno(stdout));
    worked = execute(args);
    dup2(copy1, fileno(stdin));
    dup2(copy2, fileno(stdout));

    close(f1);
    close(f2);

    free(args);

    return worked;
  }
  else if (strchr(line,'<') != NULL){
    redir_parts = parse_args(line, "<");
    //int nump;
    //for (nump = 0; redir_parts[nump] != NULL; nump++){NULL;}
    //if (nump < 2) {printf("The syntax of the command is incorrect.\n");return 0;}


    args = parse_args(redir_parts[0], " ");
    files = parse_args(redir_parts[1], " ");
    //printf("redirecting\n");

    copy = dup(fileno(stdin)); //stdin should be 0
    //printf("%s\n", redir_parts[1]);
    f =  open(files[0], O_RDONLY);

    if (f < 0){
      printf("< The system cannot find the file specified.\n");
      return 0;
    }

    dup2(f, fileno(stdin));
    worked = execute(args); //-1 = command failed
    dup2(copy, fileno(stdin));
    close(f);
    //printf("file closed\n");
    free(args);
    free(files);
    free(redir_parts);
    return worked;
  } else if (strchr(line,'>') != NULL){
    redir_parts = parse_args(line, ">");
    args = parse_args(redir_parts[0], " ");
    files = parse_args(redir_parts[1], " ");

    copy = dup(fileno(stdout)) ; //

    f =  open(files[0], O_WRONLY | O_CREAT, 0644);
    if (f < 0){
      printf("The system cannot find the file specified.\n");
      return 0;
    }
    dup2(f, fileno(stdout));
    worked = execute(args); //-1 = command failed
    dup2(copy, fileno(stdout));
    close(f);
    //printf("file closed\n");
    free(args);
    free(files);
    free(redir_parts);
    return worked;
  }
  return -2;
}

/*
int execute(char ** command);
It takes the command given as a parameter.
This executes the command given by forking.
This returns 0 if it worked!
*/
int execute(char ** args){
  if (fork() == 0){
    //printf(args[0]);
    execvp(args[0], args);
    printf("\'%s\' is not recognized as an internal or external command,\noperable program or batch file.\n", args[0]);
    return -1;
  }
  else {
    wait(NULL);
    //printf("parent: %i child: %i\n", getpid(), wait(NULL));
    //printf("%i\n", parent_pid);
  }
  return 0;
}
