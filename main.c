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
    printf("%s$ ", getcwd(dir, sizeof(dir)) ) ; // prints out current path - where we at

    fgets(line, 256, stdin) ; // transfer input to line
    *strchr(line, '\n') = '\0';
    commands = parse_args_semicolon(line) ; // these are all of the commands the user entered into the shell

      //printf("%s\n", line);
      //printf("%i\n", strcmp(line, "exit"));
    i = 0 ;
    while (commands[i] != NULL) {
      args = parse_args_space(commands[i]) ; // now the input has been separated by spaces
      //printf("%s\n", args[0]) ;

      if (strcmp(args[0], "exit") == 0){
        //printf("exiting\n");
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
      else{
        if (fork() == 0){
          execvp(args[0], args);
          printf("\'%s\' is not recognized as an internal or external command,\noperable program or batch file.\n", args[0]);
          return 0;
        }
        else {
          wait(NULL);
          //printf("parent: %i child: %i\n", getpid(), wait(NULL));
          //printf("%i\n", parent_pid);
        }
      }
      i++ ;
    }
    /*
    AN IDEA FOR WHEN WE HAVE TO SEPARATE COMMANDS BY SEMI-COLONS:
    while (commands[i] != NULL) {
      // now we look at this specific command
      args = parse_args_space(commands[i]) ;
      // args includes the command at index 0 and any additional arguments such as -l or -a for example

    } // while loop for commands is closed off here!
    */

    strcpy(line, "");
    args = '\0';
  } // end of initial while loop!!

  return 0 ;
}
