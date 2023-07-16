#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#define HS_RL_BUFSIZE 1024
#define HS_TOK_BUFSIZE 64
#define HS_TOK_DELIM " \t\r\n\a"

// Function prototypes
void hs_loop(void);
char *hs_read_line(void);

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

char *hs_read_line(void){
  char *line = NULL;
  ssize_t bufsize = 0;

  if (getline(&line,&bufsize,stdin) == -1){
    if (feof(stdin)){
      exit(EXIT_SUCCESS);
    } else {
      perror("hs: getline\n");
      exit(EXIT_FAILURE);
    }
  }
  return line;
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

int main(int argc, char **argv)
{
  hs_loop();
  return EXIT_SUCCESS;
}
