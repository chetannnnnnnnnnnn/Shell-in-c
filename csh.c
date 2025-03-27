#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define lsh_bufsize 1024
 
int int main(int argc, char *argv[]){
   csh_loop(); //run a infinite loop until the shell is closed
  return EXIT_SUCCESS;
}
void csh_loop(void){
   }

char *read_line(void){
  char *input; // the input is stored in this char
  ssize_t buff = 0; //buffsize it is initialised with 0 because it is going to be overwritten by getline
  if(getline(&input,buff,stdin) == -1){ 
    if(feof(stdin)){ // end of file
      exit(EXIT_SUCCESS);
    }else{   // we incountred a error probaly because getline cant allocate more memory
      perror(error:);
      exit(EXIT_FAILURE);
    }
  }
  return input; 
}
