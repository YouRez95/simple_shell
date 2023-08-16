#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

extern char **environ;
extern char **avs;

typedef struct Node
{
	char *data;
	struct Node *next;
} av;

char **getcommands(char **argv);


#endif /* SHELL_H */
