/**
 * _strlen - Returns the length of a string.
 * @s: The string to check
 *
 * Return: void
 */
int _strlen(char *s)
{
	int i, len = 0;

	i = 0;
	while (s[i] != '\0')
	{
		len++;
		i++;
	}

	return (len);
}
