#include "shell.h"


int _strncmp(char *s1, char *s2, int n);

/**
 * handle_cd - handle cd command
 *
 * @avs: avs
 *
 * Return: 0 success else error
 */

int handle_cd(char **avs)
{
	int beginEnviron = 0;
	char *home = NULL;
	char *old_pwd;
	char *new_pwd;
	/*char pwd[100];*/

	if (avs[1] == NULL || _strcmp(avs[1], " ") == 0)
	{
		while (*environ != NULL)
		{
			if (_strncmp(*environ, "HOME=", 5) == 0)
			{
				home = *environ + 5;
				old_pwd = getcwd(NULL, 0);
				if (chdir(home) == 0)
				{
					new_pwd = getcwd(NULL, 0);
					setenv("PWD", new_pwd, 1);
					setenv("OLDPWD", old_pwd, 1);
					free(new_pwd);
				}
				else
				{
					perror("error: ");
				}
				free(old_pwd);
				break;
			}
			beginEnviron++;
			environ++;
		}
		environ -= beginEnviron;
		free_argv(avs);
		return (0);
	}
	else
	{
		old_pwd = getcwd(NULL, 0);
		if (chdir(avs[1]) == 0)
		{
			new_pwd = getcwd(NULL, 0);
			setenv("PWD", new_pwd, 1);
			setenv("OLDPWD", old_pwd, 1);
			free(old_pwd);
			free(new_pwd);
		}
		else
		{
			perror("error 2 : ");
		}
		free_argv(avs);
		return (0);
	}
	return (0);
}


/**
 * _strncmp - compare first n byte entre two strings
 *
 * @s1: string 1
 * @s2:  string 2
 * @n: first chars want to compare
 *
 * Return: s1 == s2 ? 0 : NOT(0)
 */

int _strncmp(char *s1, char *s2, int n)
{
	int i;

	if (n > _strlen(s1) || n > _strlen(s2))
		return (1);
	for (i = 0 ; i < n ; i++)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
