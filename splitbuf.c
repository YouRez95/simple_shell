#include "shell.h"

int countdelim(char *str);

/**
 * splitbuffer - splits the buffer to substrings.
 * @buffer: to split.
 *
 * Return: a pointer to the array of substrings.
 */
char **splitbuffer(char *buffer)
{
	char **splitter_buffer;
	int i, j, words;

	words = countdelim(buffer);

	splitter_buffer = malloc(sizeof(char *) * (words + 1));
	if (!splitter_buffer)
		return (NULL);

	i = 0;
	splitter_buffer[i] = malloc(strlen(buffer) + 1);
	if (!splitter_buffer[i])
		return (NULL);

	j = 0;
	while (*buffer)
	{
		if (*buffer == ' ')
		{
			splitter_buffer[i][j] = '\0';
			i += 1;
			splitter_buffer[i] = malloc(strlen(buffer) + 1);
			if (!splitter_buffer[i])
				return (NULL);
			j = 0;
		}
		else
		{
			splitter_buffer[i][j] = *buffer;
			j++;
		}
		buffer++;
	}

	splitter_buffer[i][j] = '\0';
	splitter_buffer[i + 1] = NULL;

	return (splitter_buffer);
}

/**
 * countdelim - returns the number of words a string contains.
 * @str: the string.
 *
 * Return: int (number of words).
 */
int countdelim(char *str)
{
	int count;
	char *c;

	c = str;
	count = 1;
	while (*c)
	{
		if (*c == ' ')
			count += 1;
		c++;
	}

	return (count);
}
