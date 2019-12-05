#include "shell.h"

int main() {
  char dir[256] ;
  char line[256] ;
  int i ;
  char ** lofParseSpace ;
  char ** commands ;
  char ** args;
  while (1) {
    // INFINITE LOOP!!
    printf("%s$ ", getcwd(dir, sizeof(dir)) ) ; // prints out current path - where we at

    fgets(line, 256, stdin) ; // transfer input to line
    *strchr(line, '\n') = '\0';
    //commands = parse_args_semicolon(line) ; // these are all of the commands the user entered into the shell

    //printf("%s\n", line);
    //printf("%i\n", strcmp(line, "exit"));
    i = 0 ;
    args = parse_args_space(line) ; // now the input has been separated by spaces
    //printf("%s\n", args[0]) ;

    if (strcmp(args[0], "exit") == 0){
      //printf("exiting\n");
      return 0;
    }
    else if (strcmp(args[0], "cd") == 0) {
      // we need to change the directory to what the user typed in
      if (args[0] != NULL) {
        if (chdir(args[1]) == -1) printf("Error with changing directory: %s\n", strerror(errno)) ;
      }
      else {
        // this is just the regular cd with no additional arguments so we go back to the user

      }
    }
    else {

      /*char * i = args[0];
      int e = 1;
      while (i != NULL){
        printf("%s\n", i);
        i = args[e];
        ++e;
      }*/
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
