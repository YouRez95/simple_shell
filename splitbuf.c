#include "shell.h"

#define MAX_SUBSTRINGS 200

/**
 * splitbuffer - splits the buffer to substrings.
 * @buffer: to split.
 *
 * Return: a pointer to the array of substrings.
 */
char **splitbuffer(char *buffer)
{
	int num_substrings, buffer_len, substring_len, words, i, j;
	char **splitted_buffer;

	splitted_buffer = malloc(MAX_SUBSTRINGS * sizeof(char *));
	if (!splitted_buffer)
		return (NULL);

	buffer_len = strlen(buffer);
	num_substrings = 0;
	words = 0;
	for (i = 0; i <= buffer_len; i++)
	{
		if (buffer[i] == ' ' || buffer[i] == '\0')
		{
			substring_len = i - words;
			if (substring_len > 0)
			{
				splitted_buffer[num_substrings] = malloc(substring_len + 1);
				if (!splitted_buffer[num_substrings])
				{
					for (j = 0; j < num_substrings; j++)
						free(splitted_buffer[j]);

					free(splitted_buffer);
					num_substrings = -1;
					return (NULL);
				}
				strncpy(splitted_buffer[num_substrings], buffer + words, substring_len);
				splitted_buffer[num_substrings][substring_len] = '\0';
				num_substrings++;
			}
			words = i + 1;
		}
	}

	splitted_buffer[num_substrings] = NULL;

	return (splitted_buffer);
}
