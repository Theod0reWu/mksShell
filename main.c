#include "shell.h"

int main() {
  char dir[256] ;
  char line[256] ;
  int i ;
  char ** lofParseSpace ;
  char ** args;
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
      // we need to change the directory
      chdir("..") ;
    }
    else{
      args = parse_args_space(line);

      //char * i = args[0];
      //int e = 1;
      //while (i != NULL){
      //  printf("%s\n", i);
      //  i = args[e];
      //  ++e;
      //}
    }

    strcpy(line, "");
    args = '\0';
  }

  return 0 ;
}
