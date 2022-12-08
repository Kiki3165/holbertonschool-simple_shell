#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execmd(char **argv, char **envp)
  {
          char *command = NULL, *actual_command = NULL;
          pid_t child_pid;
          int status;
          char *file_path = NULL;
  
          child_pid = fork();
  
          /* get the command */
          command = argv[0];
  
          /*generate the path to this command before passing it to execve*/
        actual_command = get_location(command,file_path);
  
          if (!actual_command)
                  exit(1);
          if (child_pid == -1)
          {
                  perror("Error:");
                exit(1);;
          }
          if (child_pid == 0)
          {
                  /* execute the command with execve */
                  execve(actual_command, argv, envp);
                  free(actual_command);
          }
          else
          {
                  wait(&status);
          }
  }
  