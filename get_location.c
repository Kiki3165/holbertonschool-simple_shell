#include "main.h"

/**
 * get_location - get the path
 * @command: the command to enter
 * @file_path: the path of the file
 * Return: NULL
 */

char *get_location(char *command, char *file_path)
{
	char *path, *path_copy, *path_token;
	int command_length, directory_length;
	struct stat buffer;

	path = getenv("PATH");
	file_path = NULL;
	if (path)
	{
		/* Duplicate the path string -> remember to free up memory for this because*/
		 /* strdup allocates memory that needs to be freed*/
		path_copy = strdup(path);
		/* Get length of the command that was passed */
		command_length = strlen(command);

		/* Let's break down the path variable and get all the directories available*/
		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			/* Get the length of the directory*/
			directory_length = strlen(path_token);
			/* allocate memory for storing the command name*/
			 /* together with the directory name */
			file_path = calloc(sizeof(char), command_length + directory_length + 2);
			/* NB: we added 2 for the slash and null */
			 /* character we will introduce in the full command */
			/* to build the path for the command, */
			/* let's copy the directory path and concatenate the command to it */
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			/* let's test if this file path actually exists and */
			/* return it if it does, otherwise try the next directory */
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				/* return value of 0 means success implying that the file_path is valid*/
				/* free up allocated memory before returning your file_path */
				return (file_path);
			}

			else
			{
				/* free up the file_path memory so we can check for another path*/
				free(file_path);
				path_token = strtok(NULL, ":");
			}

		}
		/* if we don't get any file_path that exists for the command, we return NULL but we need to free up memory for path_copy*/

		/* before we exit without luck, let's see if the command itself is a file_path that exists */
		if (stat(command, &buffer) == 0)
		{
			free(path_copy);
			return (command);
		}
		{
			free(path_copy);
			return (command);
		}
		free(path_copy);
		return (NULL);
	}
	free(file_path);
	return (NULL);
}
