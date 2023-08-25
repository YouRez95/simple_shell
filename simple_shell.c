#include "shell.h"

void signal_handler(int i);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);

/**
 * main - entry point
 * @ac: args counter,
 * @av: args victor.
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	char		**avs =  NULL;
	char	pathname[25];
	int			status;
	pid_t		cpr;
	char *built_in[]  = {"exit", "cd"};
	unsigned long int i;
	int statCd;

	int (*handle_built_in[])(char **) = {handle_exit, handle_cd};

	(void)ac;

	signal(SIGINT, signal_handler);

	while (1)
	{
		statCd = 0;
		if (isatty(STDIN_FILENO))
			write(STDIN_FILENO, "$ ", 2);

		avs = getcommands(avs);
		if  (avs == NULL)
			exit(EXIT_FAILURE);

		if (avs[0])
		{
			for (i = 0; i < sizeof(built_in) / sizeof(built_in[0]); i++)
			{

				if (_strcmp(built_in[i], avs[0]) == 0)
				{
					if (_strcmp(avs[0], "cd") == 0)
					{
						handle_built_in[i](avs);
						statCd = 1;
						break;
					}
					exit((handle_built_in[i])(avs));
				}
			}
			if (statCd == 1)
				continue;
			cpr = fork();
			if (cpr == -1)
				exit(EXIT_FAILURE);

			if (cpr == 0)
			{

				if (execve(avs[0], avs, environ) == -1)
				{
					_strcat(_strcpy(pathname, "/bin/"), avs[0]);
					if (execve(pathname, avs, environ) == -1)
					{
						handle_error(av[0], avs[0]);
						free_argv(avs);
						exit(127);
					}
				}
			}
			else
				wait(&status);

			pathname[5] = 0;
		}
		free_argv(avs);
		if (!isatty(STDIN_FILENO) && WEXITSTATUS(status) == 127)
			exit(127);
	}
	printf("# here\n");
	return (0);
}

/**
 * signal_handler - handle action of signal 2.
 * @i: param.
 *
 * Return: void.
 */
void signal_handler(int i)
{
	char **avs;

	(void)i;
	avs = NULL;
	free_argv(getcommands(avs));
	exit(EXIT_SUCCESS);
}

/**
 * _strcpy - Copies the string pointed to by src,
 * including the terminating null byte '\0',
 * to the buffer pointed to by dest.
 * @dest: The destination
 * @src: The source
 *
 * Return: The pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';

	return (dest);
}
