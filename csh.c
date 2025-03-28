#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define lsh_bufsize 1024
#define CSH_TOK_BUFSIZE 64
#define CSH_TOK_DELIM " \t\r\n\a"
char *read_line(void){
  char *input = NULL; // the input is stored in this char
  ssize_t buff = 0; //buffsize it is initialised with 0 because it is going to be overwritten by getline
  if(getline(&input,&buff,stdin) == -1){ 
    if(feof(stdin)){ // end of file
      exit(EXIT_SUCCESS);
    }else{   //we incountred a error
      perror("error:");
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
  if (position >= buffsize){
    buffsize += CSH_TOK_BUFSIZE;
    tokens = realloc(tokens,buffsize * sizeof(char*));
    if(!tokens){
      fprintf(stderr,"csh:error in allocation\n");
       exit(EXIT_FAILURE);
    }
  }
  token = strtok(NULL,CSH_TOK_DELIM);

}
  tokens[position] = NULL;
  return tokens;
}

int csh_launch(char **args){
  pid_t pid,wpid;
  int status;


  pid = fork();
  if(pid == 0){
   if(execvp(args[0],args) == -1){
    perror("csh");
    }
    exit(EXIT_FAILURE);
  }

  else if (pid < 0){
     perror("csh");
  }else{
 do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}
int csh_cd(char **args);
int csh_help(char **args);
int csh_exit(char **args);

char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &csh_cd,
  &csh_help,
  &csh_exit
};

int csh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int csh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "csh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int csh_help(char **args)
{
  int i;
  printf("Chetan's CSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < csh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int csh_exit(char **args)
{
  return 0;
}
int csh_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < csh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return csh_launch(args);
}
void csh_loop(void){
    char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = read_line();
    args = CSH_Token(line);
    status = csh_execute(args);

    free(line);
    free(args);
  } while(status);
}
int main(int argc, char *argv[]){
  csh_loop(); //run a infinite loop until the shell is closed
  return EXIT_SUCCESS;
}

