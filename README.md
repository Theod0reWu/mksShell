# mksShell
## What does our shell implement?! Does it even do anything...:unamused:
<img src="https://media.giphy.com/media/odsNxyQQDb29O/giphy.gif" width="500" height="400"/>
Okay, so our shell doesn't set off any fireworks  <br />

**BUT** it can do the following things:   <br />
- take in commands seperated by semicolons (singular or double!)   <br />
- execute various commands such as: cd, ls, cat, echo, clear, exit, and more!   <br /> 
- allows for redirection and piping, including double redirection <br />
- allow any number of spaces can be placed between commands and other identifiers, including semicolons, piping and redirection    <br /> 
- gives correct error messages for wrong file names and other mistyped commands <br />

## Features Attempted but Unsuccessful

## Bugs & Other Things You Might Want to Know 

## Function Headers
- char ** parse_args_space(char * line) <br />
-char ** parse_args_semicolon(char * line) <br />
-int redirecting(char * line) <br />
-int execute(char ** command) <br />
-char ** parse_args(char * line, char * del) <br />
-int is_redirect(char * line) <br />
-void pipe_it_up(char * c) <br />
