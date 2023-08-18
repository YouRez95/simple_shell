#include "shell.h"

/**
 * getcommands - convert a command line to an array of strings.
 * @argv: an array to store the strings in.
 *
 * Return: a pointer to @argv in success,
 *	Null, otherwise.
*/
char **getcommands(char **argv)
{
	size_t bufsize;
	char *buffer;
	int i;

	buffer = NULL;
	bufsize = 0;
	if (getline(&buffer, &bufsize, stdin) == -1)
	{
		free(buffer);
		return (NULL);
	}

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i]  == '\n')
			buffer[i] = '\0';
		i++;
	}

	argv = splitbuffer(buffer);

	free(buffer);

	return (argv);
}
