#include "shell.h"

/**
 * handle_error - prints error message.
 * @av0: args victore [0],
 * @avs0: first element of the command line.
 *
 * Return: void.
*/
void handle_error(char *av0, char *avs0)
{
	write(STDERR_FILENO, _strcat(av0, ": 1: "),
	_strlen(av0) + 5);
	write(STDERR_FILENO, _strcat(avs0, ": not found"),
	_strlen(avs0) + 11);
	write(STDERR_FILENO, "\n", 1);
}
