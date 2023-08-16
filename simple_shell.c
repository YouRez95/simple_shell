#include "shell.h"

/**
 * main - entry point
 *
 * Return: Always 0.
 */

char **avs = NULL;

void sigint_free(int sig)
{
	int i = 0;

	while (avs[i] != NULL)
	{
		free(avs[i]);
		i++;
	}
	free(avs);
	exit(EXIT_SUCCESS);
}

int main(void)
{
	char		pathname[25];
	pid_t		cpr;
	int		status;

	signal(SIGINT, sigint_free);
	do {
		if (isatty(STDIN_FILENO))
			printf("$ ");

		avs = getcommands(avs);
		if  (avs == NULL)
			exit(EXIT_FAILURE);

		cpr = fork();
		if (cpr == -1)
			exit(EXIT_FAILURE);

		if (cpr == 0)
		{
			if (execve(avs[0], avs, environ) == -1)
			{
				strcat(strcpy(pathname, "/bin/"), avs[0]);
				if (execve(pathname, avs, environ) == -1)
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

	return (0);
}
