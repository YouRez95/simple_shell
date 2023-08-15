#include "shell.h"

/**
 * main - entry point
 *
 * Return: Always 0.
 */
int main(void)
{
	char		*buffer, *token, **av, pathname[25];
	size_t		bufsize;
	pid_t		cpr;
	int			status;

	do {
		if (isatty(STDIN_FILENO))
			printf("$ ");

		buffer = NULL;
		bufsize = 0;
		token = NULL;
		av = getcommands(buffer, bufsize, token, av);
		if  (av == NULL)
			exit(EXIT_FAILURE);

		cpr = fork();
		if (cpr == -1)
			exit(EXIT_FAILURE);

		if (cpr == 0)
		{
			if (execve(av[0], av, environ) == -1)
			{
				strcat(strcpy(pathname, "/bin/"), av[0]);
				if (execve(pathname, av, environ) == -1)
				{
					perror("./simple_shell");
					exit(EXIT_FAILURE);
				}
			}
			else
				exit(EXIT_SUCCESS);
		}
		else
			wait(&status);

		pathname[5] = 0;

	} while (1);

	free(buffer);

	return (0);
}
