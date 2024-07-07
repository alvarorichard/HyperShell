#include "hs_helpers.h"

char *builtin_str[] = 
{
    "cd",
    "help",
    "exit",
    "echo",
    "cat",
    "touch"
};

int (*builtin_func[]) (char **) = 
{
    &hs_cd,
    &hs_help,
    &hs_exit,
    &hs_echo,
    &hs_cat,
    &hs_touch
};



int hs_touch(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "hs: argumento esperado para \"touch\"\n");
        return 1;
    }

    FILE* file = fopen(args[1], "a");
    if (file == NULL)
    {
        perror("hs");
        return 1;
    }

    fclose(file);
    return 1;
}

int hs_cat(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "hs: argumento esperado para \"cat\"\n");
        return 1;
    }

    FILE* file = fopen(args[1], "r");
    if (file == NULL)
    {
        perror("hs");
        return 1;
    }

    char c;
    while ((c = fgetc(file)) != EOF)
    {
        putchar(c);
    }

    fclose(file);
    return 1;
}

int hs_echo(char **args)
{
    int i = 1;
    while (args[i] != NULL)
    {
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
    return 1;
}

int hs_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

int hs_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "hs: argumento esperado para \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("hs");
        }
    }
    return 1;
}

int hs_help(char **args)
{
    int i;
    printf("HyperShell\n");
    printf("Digite os nomes dos programas e argumentos, e pressione enter.\n");
    printf("Os seguintes comandos são nativos:\n");

    for (i = 0; i < hs_num_builtins(); i++)
    {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use o comando man para obter informações sobre outros programas.\n");
    return 1;
}

int hs_exit(char **args)
{
    return 0;
}

int hs_execute(char **args)
{
    int i;

    if (args[0] == NULL)
    {
        return 1;
    }

    for (i = 0; i < hs_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }
    return hs_launch(args);
}
