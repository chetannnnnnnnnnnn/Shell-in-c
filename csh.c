#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define lsh_bufsize 1024
#define CSH_TOK_BUFSIZE 64
#define CSH_TOK_DELIM " \t\r\n\a"
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
    }else{   //we incountred a error
      perror(error:);
      exit(EXIT_FAILURE);
    }
  }
  return input; 
}
 char **CSH_Token(char *line){
  int position = 0;
  char buffsize = CSH_TOK_BUFSIZE;
  char *token;
  char **tokens;
  tokens = malloc(buffsize * sizeof(char*));
  if(!tokens){
    fprintf(stderr,"csh:error in allocation\n");
    exit(EXIT_FAILURE);
  }
  token =  strtok(line,CSH_TOK_DELIM);
  while(token != NULL){
    tokens[position] = token;
     position++;
  }
  if (position > buffsize){
    buffsize += CSH_TOK_BUFSIZE;
    tokens = relloc(tokens,buffsize * sizeof(char*));
    if(!tokens){
      fprintf(stderr,"csh:error in allocation\n");
       exit(EXIT_FAILURE);
    }
   token = strtok(NULL,CSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}
