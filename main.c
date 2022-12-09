#include "main.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **argv, char **envp)
{
	char *prompt = "";
	char *lineptr = NULL, *lineptr_copy = NULL;
	size_t n = 0;
	/*ssize_t nchars_read;*/
	const char *delim = "\n ";
	int num_tokens = 0;
	char *token;
	int i;
	/* declaring void variables */
	(void)ac;	


	while (1) {
		if (isatty(STDIN_FILENO))
			printf("%s", prompt);
		getline(&lineptr, &n, stdin);
		
		if(feof(stdin))
		{
			break;
		}
		else if (strcmp("exit\n",lineptr) == 0)
		{
			break;
		}
		else if (strcmp("env\n",lineptr) == 0)
		{
			char **env;
			for (env = envp; *env != 0; env++)
			{
				char *thisEnv = *env;
				printf("%s\n", thisEnv);
			}
		}
	    else
	    {
        /* check if the getline function failed or reached EOF or user use CTRL + D */ 


        /********** split the string (lineptr) into an array of words ********/
        /* calculate the total number of tokens */
        token = strtok(lineptr, delim);

        while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}
        num_tokens++;

        /* Allocate space to hold the array of strings */
         argv = calloc(sizeof(char *), num_tokens);
	if (!argv)
		exit(1);
        /* Store each token in the argv array */
	token = strtok(lineptr, delim);
	
	for (i = 0; token != NULL; i++){
		argv[i] = token;
		token = strtok(NULL, delim);
        }
	argv[i] = NULL;

        /* execute the command */
	execmd(argv,envp);
	
	for (i = 0; token != NULL; i++)
		free(argv[i]);
        free(argv);
	    }
    }
    free(lineptr);
    /* free up allocated memory */ 
    return (0);
}
