#include "shell.h"

int main() {
  char dir[256] ;
  char line[256] ;
  int i ;
  char ** lofParseSpace ;
  while (1) {
    // INFINITE LOOP!!
    printf("%s$ ", getcwd(dir, sizeof(dir)) ) ; // prints out current path - where we at

    fgets(line, 256, stdin) ; // transfer input to line
    *strchr(line, '\n') = '\0';

    //printf("%s\n", line);
    //printf("%i\n", strcmp(line, "exit"));
    if (strcmp(line, "exit") == 0){
      //printf("exiting\n");
      return 0;
    }
    else if (strcmp(line, "cd")) {
      // we are changing directories
      chdir("..") ;
    }
    else{}
    printf("%s\n", line);

    strcpy(line, "");
  }

  return 0 ;
}
