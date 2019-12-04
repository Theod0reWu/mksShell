#include "shell.h"

int main() {
  char dir[256] ;
  char line[256] ;
  int i ;
  char ** lofParseSpace ;
  char line[256];
  while (1) {
    // INFINITE LOOP!!
    printf("%s$ ", getcwd(dir, sizeof(dir)) ) ; // prints out current path - where we at
    scanf("%[^\n]", line) ;

    fgets(line, 256, stdin) ; // transfer input to line

    if (strcmp(line, "exit")){
      return 0;
    }
    printf("%s\n", line);

    strcpy(line, "");
  }

  return 0 ;
}
