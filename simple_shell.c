#include "shell.h"

void signal_handler(int i);

/**
 * main - entry point
 *
 * Return: Always 0.
 */
int main(void)
{
	char		**avs =  NULL;
	char	pathname[25];
	int			status;
	pid_t		cpr;
	char *built_in[]  = {"exit"};
	unsigned long int i;

	int (*handle_built_in[])(char **) = {handle_exit};

	signal(SIGINT, signal_handler);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		avs = getcommands(avs);
		if  (avs == NULL)
			exit(EXIT_FAILURE);

		for (i = 0; i < sizeof(built_in) / sizeof(built_in[0]); i++)
		{
			if (strcmp(built_in[i], avs[0]) == 0)
				return (handle_built_in[i](avs));
		}
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
					free_argv(avs);
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
