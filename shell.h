#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>

#include <math.h>

#include <signal.h>

char ** parse_args_space(char * line) ;
char ** parse_args_semicolon(char * line) ;
int redirecting(char * line) ;
int execute(char ** command) ;
char ** parse_args(char * line, char * del) ;
//int pipe(char ** args);
int is_redirect(char * line) ;
void pipe_it_up(char * c) ;
