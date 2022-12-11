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
		path_copy = strdup(path);
		command_length = strlen(command);
		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			directory_length = strlen(path_token);
			file_path = calloc(sizeof(char), command_length + directory_length + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}

			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}

		}
		if (stat(command, &buffer) == 0)
		{
			free(path_copy);
			return (command);
		}
		else
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
