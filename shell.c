#include "shell.h"

/*
You (and a partner if desired - highly suggested) are to write a shell.
The shell should implement as many of these features as possible.
The first being the most basic up to the last which is the most complex.
1. Read a line at a time, parse the line to separate the command from its arguments.
   It should then fork and exec the command. The parent process should wait until
   the exec'd program exits and then it should read the next command.
   Note: exit and cd cannot be run through a forked child process, you will have to implement these commands on your own.
         check out the chdir() function
2. Read and separate multiple commands on one line with ;.
   That is, the line ls -l ; echo hello should first run the command ls -l and then echo hello.
3. Implement simple redirection using > (redirecting stdout) and < (redirecting stdin).
4. Implement simple pipes, that is: ls | wc would run ls and use the output from ls as the input for wc.
   Check out popen() for this.

All of these commands work in bash, so use it to check out the functionality of each feature if you are unclear about anything.

Specific requirements
1. Every function you write must have a function header describing the arguments, return value and what the function does.
  - Use modular design liberally. This is a large program.
2. You should have a readme file with the following:
  - A description of what features your shell implements
  - A description of what features you attempted to implement but were unsuccessful
  - Any bugs or things you want me to know about your program
  - A copy of every function header
  - An example of the readme file can be found in the github repository for this assignment
3. This project should use separate C files as necessary.
4. The project should be built using make and a makefile, I will only compile by using make.

Try starting with these restrictions on input:
- To make your life easier, you could require that all items on the command line are to be separated by a single space.
- When parsing the line, it might help to count the number of tokens (individual pieces), before parsing.
- You can restrict the locations and ordering of > and <.
- You can limit piping (|) to a single pipe.
*/

/*
char ** parse_args_semicolon(char * line) ;
The line argument is what was typed into the shell.
It separates what was typed in at the semicolons and puts each command into char ** args
returns char ** a, which is the array of the command and any arguments it comes with
*/
char ** parse_args_semicolon(char * line) {
  char ** a = calloc(256, sizeof(char **)) ;
  int i ;
  char * q ;
  for (i = 0 ; (q = strsep(&line, ";")) ; i++) {
    if (strcmp(q,"") != 0){
      a[i] = q ;
    }
    else {
      i-- ;
    }
    //printf("|%s|\n",a[i] );
  }
  return a ;
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

char ** parse_args(char * line, char * del) {
  char ** a = calloc(256, sizeof(char **)) ;
  int i ;
  char * q ;
  for (i = 0 ; (q = strsep(&line, del)) ; i++) {
    if (strcmp(q,"") != 0){
      a[i] = q ;
    }else{i--;}
    //printf("|%s|\n",a[i] );
  }
  return a ;
}

/*
*/
int is_dir(char * line){
  return strchr(line, '<') == NULL && strchr(line, '>') == NULL;
}

/*
*/
int pipe(char ** args) {
  FILE * p ;
  char ch ;
  p = popen(args[],"r"); /* Unix */
  if (p == NULL) {
    printf("What process are you trying to run??!!\n") ;
    return 1 ;
  }
  else {
    // execute
    execvp(args[2], args) ;
  }
  while ( (ch = fgetc(p)) != EOF) {
    putchar(ch) ;
    pclose(p) ;

    return 0;
}

/*
void redirecting(char ** args);
The argument is the redirection command with either > or < (but these are not as the first argument)
The next thing after the >,< should be the file name
This executes the command and returns 0 if it worked
*/
int redirecting(char * line){
  int f;
  int copy;
  int worked = 0;
  char ** redir_parts;
  char ** args;

  if (strcmp(redir,"<") == 0){
    redir_parts = parse_args(line, ">");
    args = parse_args(redir_parts[0], " ");
    //printf("redirecting\n");
    copy = dup(fileno(stdin)); //stdin should be 0
    f =  open(args[i], O_RDONLY);

    if (f < 0){
      printf("The system cannot find the file specified.\n");
      return 0;
    }

    dup2(f, fileno(stdin));
    args[i-1] = '\0';
    worked = execute(args); //-1 = command failed
    dup2(copy, fileno(stdin));
    close(f);
    //printf("file closed\n");
    return worked;
  } else if (strcmp(redir,">") == 0){
    // here is what happens when it's the ">" sign instead
    //printf("Redirecting!\n") ;
    copy = dup(fileno(stdout)) ; //
  }

  return -2;
}

/*
int execute(char ** command);
It takes the command given
This executes the command given by forking
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
