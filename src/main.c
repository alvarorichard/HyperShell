#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

int  main(int argc, char **argv)
{

  hs_loop();
  return EXIT_SUCCESS;

  
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
