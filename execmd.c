#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/**
* execmd - Entry point
* Description: 'execute the command'
* Return: int
* @argv: char envp
* @envp: char envp
*/

int execmd(char **argv, char **envp)
{
	char *command = NULL, *actual_command = NULL;
	pid_t child_pid;
	int status;
	char *file_path;

	file_path = NULL;


	/* get the command */
	command = argv[0];

	/*generate the path to this command before passing it to execve*/
	actual_command = get_location(command, file_path);


	child_pid = fork();


	if (!actual_command)
		exit(1);
	if (child_pid == -1)
	{
		perror("Error:");
		exit(1);
	}
	if (child_pid == 0)
	{
		/* execute the command with execve */
		execve(actual_command, argv, envp);
		free(actual_command);
	}
	wait(&status);
	if (status == 152)
	{
		free(actual_command);
		return (-1);
	}
	return (0);
}
