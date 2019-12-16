#include "shell.h"

int main() {
  char dir[256] ;
  char line[256] ;
  int i ;
  char ** commands ;
  char ** args;
  int parent_pid = getpid();
  while (1) {
    // INFINITE LOOP!!
    //printf("%i\n", fileno(stdin));
    printf("%s$ ", getcwd(dir, sizeof(dir)) ) ; // prints out current path - where we at
    fgets(line, 256, stdin) ; // transfer input to line
    //printf("|%s|\n", line);

    *strchr(line, '\n') = '\0';
    commands = parse_args_semicolon(line) ; // these are all of the commands the user entered into the shell

    //printf("%s\n", line);
    //printf("%i\n", strcmp(line, "exit"));
    i = 0 ;
    char commandcopy[256] ;
    while (commands[i] != NULL) {
      strcpy(commandcopy, commands[i]) ;
      args = parse_args_space(commandcopy) ; // now the input has been separated by spaces

      if (strcmp(args[0], "exit") == 0){
        //printf("exiting\n");
        //printf("Parent id: %d\n", getppid()) ;
        return 0;
      }

      else if (strcmp(args[0], "cd") == 0) {
        // we need to change the directory to what the user typed in
        //printf("|%s|\n", args[1]);
        if (args[1] != NULL && strcmp(args[1], "") != 0 && strcmp(args[1], "~") != 0) {
          if (chdir(args[1]) == -1) printf("Error with changing directory: %s\n", strerror(errno)) ;
        }
        else {
          // go to the home directory instead
          chdir(getpwuid(getuid())->pw_dir) ;
        }
      }

      else {
        //printf("%s\n",commands[i] );
        //printf("%i\n",is_redirect(commands[i]) );
        int w = 0;
        if (is_redirect(commands[i])){
          //printf("is redirecting\n");
          if (redirecting(commands[i]) == -1) return -1;
          w = 1;
        }
        else if (strchr(commands[i], '|') != NULL) {
          if (pipe_it_up(commands[i]) == -1) return -1 ;
        }
        else if (execute(args) != 0) {
          return -1; //if the child did not execute properly, kill the child process
        }
      }
      i++ ;
      free(args);
    }

    strcpy(line, "");
    free(commands);
    //args = '\0';
  } // end of initial while loop!!
  return 0 ;
}
