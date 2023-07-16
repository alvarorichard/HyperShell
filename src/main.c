#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <string.h>

#define HS_RL_BUFSIZE 1024
#define HS_TOK_BUFSIZE 64
#define HS_TOK_DELIM " \t\r\n\a"

// Function prototypes
void hs_loop(void);
char *hs_read_line(void);
char **hs_split_line(char *line);
int hs_execute(char **args);
int hs_launch(char **args);
int hs_cd(char **args);
int hs_help(char **args);
int hs_exit(char **args);

char *hs_read_line(void){
  int bufsize = HS_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "hs: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while(1){
    c = getchar();

    if (c == EOF || c == '\n'){
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if(position >= bufsize){
      bufsize += HS_RL_BUFSIZE;  
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "hs: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

void hs_loop(void){
  char*line;
  char**args;
  char status;

  do
  {
    printf(">> ");
    line = hs_read_line();
    args = hs_split_line(line);
    status = hs_execute(args);
    free(line);
    free(args);
  } while (status);
  
}

char **hs_split_line(char *line){
  int bufsize = HS_TOK_BUFSIZE,position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens){
    fprintf(stderr,"hs: erro de alocacao\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line,HS_TOK_DELIM);
  while (token != NULL)
  {
    tokens[position] = token;
    position++;

    if(position >= bufsize){
      bufsize += HS_TOK_BUFSIZE;
      tokens = realloc(tokens,bufsize * sizeof(char*));
      if (!tokens){
        fprintf(stderr,"hs: erro de alocacao\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL,HS_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

int hs_launch(char **args){
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0){
    if (execvp(args[0],args) == -1){
      perror("hs");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0){
    perror("hs");
  } else {
    do
    {
      wpid = waitpid(pid,&status,WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    
  }
  return 1;
}

char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &hs_cd,
  &hs_help,
  &hs_exit
};

int hs_num_builtins(){
  return sizeof(builtin_str) / sizeof(char *);
}

int hs_cd(char **args){
  if (args[1] == NULL){
    fprintf(stderr,"hs: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0){
      perror("hs");
    }
  }
  return 1;
}

int hs_help(char **args){
  int i;
  printf("HyperShell\n");
  printf("Digite os nomes dos programas e argumentos, e pressione enter.\n");
  printf("Os seguintes comandos sao nativos:\n");

  for (i = 0; i < hs_num_builtins(); i++){
    printf("  %s\n",builtin_str[i]);
  }
 
 printf("use o comando man para obter informacoes sobre outros programas.\n");
  return 1;

}

int hs_exit(char **args){
  return 0;
}

int hs_execute(char **args){
  int i;

  if (args[0] == NULL){
    return 1;
  }

  for (i = 0; i < hs_num_builtins(); i++){
    if (strcmp(args[0],builtin_str[i]) == 0){
      return (*builtin_func[i])(args);
    }
  }
  return hs_launch(args);
}

int main(int argc, char **argv)
{
  hs_loop();
  return EXIT_SUCCESS;
}
