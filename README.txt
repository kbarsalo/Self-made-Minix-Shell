Author: Katherine Barsaloux
CMPS 111
PA 1: README.txt

------------------------------------------------------------------
BUGS:
1. If the user enters ">" the command works,
but the user is forced to enter "exit" after because of an infinite loop.

2. If the user inputs, for example, "sleep 5 &", before any other input, the background
process will not run correctly as it will be blocked. To fix this type "ls" enter 
then you can use & correctly. 


-------------------------------------------------------------------

TO RUN PROGRAM:
1. Type "make" into the Minix command line. (Ignore warnings.)
2. Type "./shell". You are now inside the new shell.
3. BEFORE TESTING NOTE THE BUGS AT THE TOP. 
4. Type "ls". It should list your current directory. 
5. Type "ls -l". It should list what you have access to and what was modified when. 
6. Type "sort < numbers.txt". The output should be ordered numbers. 
7. Test to your lesuire, remember the bugs. 

----------------------------------------------------------------------

shell.c
    Most of the basic idea is in the DESIGN file. 
I added a few headers like:
#include <string.h>
#include <stdbool.h>
#include <signal.h>

The string.h is for when I append the argument strings to be returned in the 
parse function. 

The stdbool.h is for the bool background I set to check for a background process
and wait on that parent to finish. 

The signal.h is for signal, but I changed it to sigaction when I could not get signal to
run correctly on Minix.


It's important to note for my shell.c it's made up into three parts. My parse function, my execution function,
and the fork command. My fork command is in my main after parse and execute function are done. I did this to
think of the program in steps.  

 
