#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

char *get_location(char *command,char *file_path);
int execmd(char **argv, char **envp);

#endif
