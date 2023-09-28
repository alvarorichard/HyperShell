#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HS_RL_BUFSIZE 1024
#define HS_TOK_BUFSIZE 64
#define HS_TOK_DELIM " \t\r\n\a"

void hs_loop(void);
char *hs_read_line(void);
char **hs_split_line(char *line);
int hs_execute(char **args);
int hs_launch(char **args);
int hs_cd(char **args);
int hs_help(char **args);
int hs_exit(char **args);
int hs_echo(char **args);
int hs_cat(char **args);
int hs_touch(char **args);




