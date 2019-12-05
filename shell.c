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
returns char ** args
*/
char ** parse_args_semicolon(char * line) {

}



/*
char ** parse_args(char * line) ;
The line argument is the command typed into the shell.
It seperates this command at the spaces and puts each part into char ** args
returns char ** args
 */
char ** parse_args_space(char * line) {
  //char ** args = calloc(256, sizeof(char *)) ;
  char ** args = malloc(500) ;
  char * current = strsep(&line, " ") ;
  int x = 0 ;
  while (current) {
    //printf("%s\n", current) ;
    args[x] = current ;
    // keep going to check for more arguments
    current = strsep(&line, " ") ;
    x++ ;
  }
  return args ;
}
