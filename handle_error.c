#include "shell.h"

/**
 * handle_error - prints error message.
 * @av0: args victore [0],
 * @avs: the command line as an array.
 *
 * Return: void.
*/
void handle_error(char *av0, char **avs)
{
	if (_strcmp(avs[0], "exit") == 0)
	{
		write(STDERR_FILENO, _strcat(av0, ": 1: "),
		_strlen(av0) + 5);
		write(STDERR_FILENO, _strcat(avs[0], ": Illegal number: "),
		_strlen(avs[0]) + 18);
		write(STDERR_FILENO, avs[1],
		_strlen(avs[1]));
		write(STDERR_FILENO, "\n", 1);
	}
	else
	{
		write(STDERR_FILENO, _strcat(av0, ": 1: "),
		_strlen(av0) + 5);
		write(STDERR_FILENO, _strcat(avs[0], ": not found"),
		_strlen(avs[0]) + 11);
		write(STDERR_FILENO, "\n", 1);
	}
}
