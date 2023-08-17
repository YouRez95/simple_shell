#include "shell.h"

void signal_handler(int i);

/**
 * main - entry point
 *
 * Return: Always 0.
 */
int main(void)
{
	char		**avs, pathname[25];
	int			status;
	pid_t		cpr;

	signal(SIGINT, signal_handler);

	while (1)
	{
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
		}
		else
			wait(&status);

		free_argv(avs);
		pathname[5] = 0;
	}

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
