#include "shell.h"

/**
 * free_argv - frees the array of argvs.
 * @arr: the array of strings to be freed,
 *
 * Return: void.
*/
void free_argv(char **arr)
{
	int a;

	for (a = 0; arr[a] != NULL; a++)
		free(arr[a]);

	free(arr);
}
