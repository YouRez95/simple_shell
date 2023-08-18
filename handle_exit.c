#include "shell.h"

/**
 * handle_exit - handle the exit command with status
 *
 * @avs: array of strings
 *
 * Return: status ? status : 0
 */

int handle_exit(char **avs)
{
	int status;

	if (avs[1])
	{
		status = atoi(avs[1]);
		free_argv(avs);
		return (status);
	}
	free_argv(avs);
	return (0);
}
