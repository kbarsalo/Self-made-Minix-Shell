/*Author: Katherine Barsaloux */
/*CMPS 111*/
/*PA 1: shell.c*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

extern char **get_line(void);
char* in;
char* out;
bool background = false;

/* Takes the user input stored in args and parses it.
   Mainly used to handle the "<, >, &" cases.
   Params: The char array that holds the user's commands.
   Returns: The newly modified args to be executed at a later time.
*/
char** parse(char** args){
   char ** tmp;
   int i;
   int k = 0;

   if (args[0] == NULL) return NULL;

   /*Does instruction 1 from PDF.
     If the first argument is "exit"
     then the shell ends
   */
   if (!strcmp("exit", args[0])){
        exit(0);
   }

   /*Sets the soon to be modified character array to fixed size.*/
   tmp = malloc(sizeof(char*)*10);

   /*Check for cases*/
   for(i = 0; args[i] != NULL; i++){
      char* c = args[i];
      switch(c[0]){

         /* Tells the shell to run a program in the background. */
         case '&':
                 background = true;
                 sigaction(SIG_IGN, SIGCHLD, NULL);/*should not block background processor */
                 break;

         /* Redirects information to a chosen file. */
         case '>':
                 if(args[i++] != NULL){
                    out = strdup(args[i]); /* out is set to where the information will be stored. */
                 }
                 break;


         case '<':
                 if(args[i++] != NULL){
                    in = strdup(args[i]); /* in is set to where the information is being loaded */
                 }
                 break;

         /*If none of the cases are hit then the new argument tmp appends the arg[i]*/
         default:
                /* Note: tmp[0] should hold the command that will execute the other arguments */
                tmp[k++] = strdup(args[i]);
                break;

      }
   }
   tmp[k+1] = NULL; /*Sets null pointer*/
   return tmp;

}


/*
After the user's arguments have been modified this function
executes the work accordingly.
Param: Takes in the newly parsed arguments (character array).
*/
void execute(char** args){

/*For the read and write directions*/
   if(in != NULL){
      freopen(in, "r", stdin); /* Reads the file "in" and outputs to terminal. */
   }

   /*BUG: Works but the shell must "exit" after due to endless loop*/
   if(out != NULL){
       freopen(out, "w", stdout); /* Writes information to the "out" file. */
   }

   /* Tells the shell to execute the modified arguments. */
   execvp(args[0], args);

   exit(1);
}

int main(int argc, char *argv[]) {
  int i;
  int status;
  char **args;
  pid_t pid;

      while(1) {
          args = get_line(); /* stores each line in array */

          /*If the user types in nothing, you won't get a horrible seg fault. */
          if (args[0] == NULL) continue;

          /*Holds the newly parsed arguments. */
          args = parse(args);

          /*Is set based on the if another processor is called*/
          pid = fork();
          if(pid == 0){ /*run child*/
             execute(args);
             exit(1);

          }else if(pid < 0){ /* This should never happen */
             printf("Forking child failed!");
             exit(1);
          }

          /* Wait may not work correctly. */
          else{
              if(background){
                 wait(&status); /*Tells the parent to wait while the child finishes.*/
              }
          }
       }
       return 0;
}
