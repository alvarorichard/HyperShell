#include "hs_helpers.h"

char** hs_split_line(char* line)
{
    int     bufsize = HS_TOK_BUFSIZE;
    int     position = 0;
    char**  tokens = malloc(bufsize * sizeof(char*));
    char*   token;

    if (!tokens)
    {
        fprintf(stderr, "hs: Erro de alocação\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, HS_TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += HS_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens)
            {
                fprintf(stderr, "hs: Erro de alocação\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, HS_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
