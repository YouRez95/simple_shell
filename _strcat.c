/**
 * _strcat - Concatenates two strings.
 * @src: The source sting
 * @dest: The destination
 *
 * Return: The pointer to the resulting string dest.
 */
char *_strcat(char *dest, char *src)
{
	int i, j, k, destlen = 0, strlen = 0;

	i = 0;
	while (src[i] != '\0')
	{
		strlen++;
		i++;
	}

	i = 0;
	while (dest[i] != '\0')
	{
		destlen++;
		i++;
	}

	j = i + strlen;
	k = 0;
	while (i <= j)
	{
		dest[i] = src[k];
		i++;
		k++;
	}

	return (dest);
}
