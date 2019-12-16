#include "shell.h"

/*
char ** parse_args(char * line) ;
Argument: what is typed into the shell
Separates what was typed in at del (the delimiter) and puts each command into char ** args
Returns: char ** a, which is an array
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
Argument: what is typed into the shell
Separates what was typed in at the semicolons and puts each command into char ** args
Returns: an array of the commands typed in to run
This calls parse_args so it was created more for convenience
*/
char ** parse_args_semicolon(char * line) {
  return parse_args(line, ";") ;
}

/*
char ** parse_args_space(char * line) ;
Argument: the command given
Separates this command at the spaces and puts each part into char ** args && it gets rid of extra spaces that used to cause issues!
Returns: an array of the command and any arguments it comes with
 */
char ** parse_args_space(char * line) {
  return parse_args(line, " ") ;
}

/*
int is_redirect(char * line) ;
Argument: the line or command given
Checks whether there will be redirecting or not
Returns 1 if the command involves redirection
*/
int is_redirect(char * line) {
  return strchr(line, '<') != NULL || strchr(line, '>') != NULL;
}

/*
void redirecting(char ** args);
Argument: the redirection command with either > or < (but these are not as the first argument)
The next thing after the >,< should be the file name
Executes the command
Returns 0 if it worked
*/
int redirecting(char * line) {
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
int pipe_it_up(char ** line) ;
Argument: the user input given (the command)
Uses input to determine which 2 commands need to be run
Identifies the first and second commands, executes the first one if possible,
and then pipes!
Returns 0 if successful and returns -1 if something went wrong.
*/
int pipe_it_up(char * c) {
  char ** args = parse_args(c, "|") ;
  char ** first = parse_args_space(args[0]) ;
  char ** second = parse_args_space(args[1]) ;
  int fd[2] ;
  int p ;
  int backup = dup(0) ;
  int backup2 = dup(1) ;
  pipe(fd) ;
  p = fork() ;
  if (p) {
    close(fd[1]) ;
    backup = dup(0) ;
    dup2(fd[0], 0) ;
    if (execvp(second[0], second) == -1) {
      printf("Error with first command: %s\n", strerror(errno)) ;
      return -1 ;
    }
    dup2(backup, 0) ;
    close(backup) ;
    close(fd[0]) ;
  }
  else {
    close(fd[0]) ;
    backup2 = dup(1) ;
    dup2(fd[1], 1) ;
    if (execvp(first[0], first) == -1) {
      printf("Error with first command: %s\n", strerror(errno)) ;
      return -1 ;
    }
    dup2(backup2, 1) ;
    close(backup2) ;
    close(fd[1]) ;
  }
  return 0 ;
}

/*
int execute(char ** command);
Argument: the command given
Executes the command given by forking
Returns 0 if it worked!
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
