#include "shell.h"

/**
 * free_argv - frees the array of argvs.
 * @arr: the array of strings to be freed,
 *
 * Return: void.
*/
void free_argv(char **arr)
{
	int a = 0;

	while (arr[a] != NULL)
	{
		free(arr[a]);
		a++;
	}

	free(arr);
}
