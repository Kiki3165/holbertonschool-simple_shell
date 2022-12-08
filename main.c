#include "main.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **argv, char **envp)
{
	char *prompt = "(Eshell) $ ";
	char *lineptr = NULL, *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	int num_tokens = 0;
	char *token;
	int i;
	/* declaring void variables */
	(void)ac;	

/* allocate space for a copy of the lineptr */
          lineptr_copy = malloc(sizeof(char) * 1024);
	  if (lineptr_copy== NULL)
          {
                  perror("tsh: memory allocation error");
          }
	/* Create a loop for the shell's prompt */
	while (1) {
		printf("%s", prompt);
		nchars_read = getline(&lineptr, &n, stdin);
		
		if(feof(stdin))
		{
			printf("\n");
			break;
		}
		else if (strcmp("exit\n",lineptr) == 0)
		{
			break;
		}
		else if (strcmp("env\n",lineptr) == 0)
		{
			for (char **env = envp; *env != 0; env++)
			{
				char *thisEnv = *env;
				printf("%s\n", thisEnv);
			}
		}
	    else
	    {
        /* check if the getline function failed or reached EOF or user use CTRL + D */
        /* copy lineptr to lineptr_copy */
        strcpy(lineptr_copy, lineptr);

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
         argv = malloc(sizeof(char *) * num_tokens);
	if (!argv)
		exit(1);
        /* Store each token in the argv array */
	token = strtok(lineptr_copy, delim);
	
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
	free(lineptr_copy);    
    /* free up allocated memory */ 
    return (0);
}
