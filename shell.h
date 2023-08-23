#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

extern char **environ;

/**
 * struct Node - singly linked list
 * @data: string - (malloc'ed string)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct Node
{
	char *data;
	struct Node *next;
} av;

char **getcommands(char **argv);
char **splitbuffer(char *buffer);
void free_argv(char **arr);
int handle_exit(char **arr);
#endif /* SHELL_H */
