#include "main.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **argv, char **envp)
{
    char *prompt = "";
    char *lineptr = NULL;
    size_t n = 0;
    /*ssize_t nchars_read;*/
    const char *delim = "\n \t";
    char *token;
    char **env;
    int i;
    /* declaring void variables */
    (void)ac;

    /* Allocate space to hold the array of strings */
    argv = calloc(sizeof(char *), 1024);
    if (!argv)
        exit(1);

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("%s", prompt);
        getline(&lineptr, &n, stdin);

        if (feof(stdin))
            break;
        else if (strcmp("exit\n", lineptr) == 0)
            exit(1);
        else if (strcmp("env\n", lineptr) == 0)
        {
            for (env = envp; *env != 0; env++)
            {
                char *thisEnv = *env;
                printf("%s\n", thisEnv);
            }
        }
        else
        {
            /* Store each token in the argv array */
            token = strtok(lineptr, delim);

            if (token == NULL)
            {
                free(lineptr);
                free(argv);
                exit(0);
            }
            for (i = 0; token != NULL; i++)
            {
                argv[i] = NULL;
                argv[i] = token;
                token = strtok(NULL, delim);
            }
            argv[i] = NULL;

            /* execute the command */
            execmd(argv, envp);

        }
    }
    free(lineptr);
    free(argv);
    /* free up allocated memory */
    return (0);
}
