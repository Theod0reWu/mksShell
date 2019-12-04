#include "shell.h"

int main() {
  char dir[256] ;
  int i ;
  char ** lofParseSpace ;
  while (1) {
    // INFINITE LOOP!!
    printf("%s$ \n", getcwd(dir, sizeof(dir)) ) ; // prints out current path - where we at

    char * line = malloc(256) ;
    fgets(line, 256, stdin) ; // transfer input to line
    char ** args = parse_args_semicolon(line) ; // let's see what our command is

    for (i = 0 ; i < 256 ; i++) {
      if (args[i] != NULL) {
        lofParseSpace = parse_args_space(args[i]) ;
      }
    }
    strcpy(line, "");
  }
  
  return 0 ;
}
