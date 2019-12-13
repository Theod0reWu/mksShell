# mksShell
## What does our shell implement?! Does it even do anything...:unamused:
<img src="https://media.giphy.com/media/odsNxyQQDb29O/giphy.gif" width="500" height="400"/>

_Okay, so our shell doesn't set off any fireworks_  <br />

**BUT** it can do the following things:   <br />
- take in commands seperated by semicolons (singular or double!)   <br />
- execute various commands such as: cd, ls, cat, echo, clear, exit, and more!   <br /> 
- allows for redirection and piping, including double redirection <br />
- allow any number of spaces can be placed between commands and other identifiers, including semicolons, piping and redirection    <br /> 
- gives correct error messages for wrong file names and other mistyped commands <br />

## Features Attempted but Unsuccessful

## Bugs & Other Things You Might Want to Know 

## Function Headers
#### char ** parse_args(char * line) ;
  - Argument: what is typed into the shell
  - Separates what was typed in at del (the delimiter) and puts each command into char ** args
  - Returns: char ** a, which is an array
#### char ** parse_args_semicolon(char * line) ;
  - Argument: what is typed into the shell
  - Separates what was typed in at the semicolons and puts each command into char ** args
  - Returns: an array of the commands typed in to run
  - _This calls parse_args so it was created more for convenience_
#### char ** parse_args_space(char * line) ;
  - Argument: the command given
  - Separates this command at the spaces and puts each part into char ** args && it gets rid of extra spaces that used to cause issues!
  - Returns: an array of the command and any arguments it comes with
#### int is_redirect(char * line) ;
  - Argument: the line or command given
  - Checks whether there will be redirecting or not
  - Returns
#### int redirecting(char * line) ;
  - Argument: the redirection command with either > or < (but these are not as the first argument)
  - The next thing after the >,< should be the file name
  - Executes the command
  - Returns 0 if it worked
#### void pipe_it_up(char * c) ;
  - Argument: the user input given
  - Uses input to determine which commands need to be run
  - Identifies the first and second commands, executes the first one if possible, and then uses the output from the first command as the input to the second command that comes after the |.
  - Does not return anything, but it will print and get errno involved when there is something wrong with one or more of the commands.
#### int execute(char ** command) ;
  - Argument: the command given
  - Executes the command given by forking
  - Returns 0 if it worked!
