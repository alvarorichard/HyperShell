#include "hs_helpers.h"

char* hs_read_line(void)
{
    int     bufsize = HS_RL_BUFSIZE;
    int     position = 0;
    char*   buffer = malloc(sizeof(char) * bufsize);
    int     c;
            

    if (!buffer)
    {
        fprintf(stderr, "hs: Erro de alocação\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        c = getchar();

        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize)
        {
            bufsize += HS_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "hs: Erro de alocação\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
