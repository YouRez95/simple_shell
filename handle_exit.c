#include "shell.h"

int _atoi(char *s);

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
		status = _atoi(avs[1]);
		free_argv(avs);
		return (status);
	}
	free_argv(avs);
	return (0);
}


/**
 * _atoi - convert string to integer
 *
 * @s: string
 *
 * Return: string converted
 */

int _atoi(char *s)
{
	int i, sign, result = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[0] == '-')
			sign = -1;
		else
			sign = 1;

		if (s[i] >= '0' && s[i] <= '9')
			result = result * 10 + (s[i] - '0');
	}

	return (result * sign);
}
