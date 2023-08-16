#include "shell.h"

av *add_at_end(av **head, char *token);
void free_av(av *head);

/**
 * getcommands - convert a command line to an array of strings.
 * @buffer: where to save the command line in,
 * @bufsize: size of the buffer,
 * @token: to store the strings we get from the cmd,
 * @argv: an array to store the strings in.
 *
 * Return: a pointer to @argv in success,
 *	Null, otherwise.
*/
char **getcommands(char **argv)
{
	size_t bufsize;
	char *buffer, *token;
	av *head, *ptr;
	int i, listlen;

	buffer = NULL;
	bufsize = 0;
	token = NULL;
	if (getline(&buffer, &bufsize, stdin) == -1)
		return (NULL);

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i]  == '\n')
			buffer[i] = '\0';
		i++;
	}

	head = malloc(sizeof(av));
	if (head == NULL)
		return (NULL);

	head->data = strtok(buffer, " ");
	head->next = NULL;

	listlen = 1;
	token = strtok(NULL, " ");
	while (token != NULL)
	{
		add_at_end(&head, token);
		token = strtok(NULL, " ");
		listlen++;
	}

	argv = malloc((listlen + 1) * sizeof(char *));
	if (argv == NULL)
	{
		fprintf(stderr, "memory allocation failed\n");
		return (NULL);
	}

	ptr = head;
	for (i = 0; i < listlen; i++)
	{
		argv[i] = malloc(strlen(ptr->data) * sizeof(char));
		if (argv == NULL)
		{
			fprintf(stderr, "allocation memory failed\n");
			return (NULL);
		}
		strcpy(argv[i], ptr->data);
		ptr = ptr->next;
	}

	argv[i] = NULL;

	free_av(head);

	return (argv);
}

/**
 * add_at_end - add a node at the end of a list.
 * @head: a linked list,
 * @str: data to put in the created node.
 *
 * Return: a pointer to created node,
 *	Null, otherwise.
*/
av *add_at_end(av **head, char *str)
{
	av *newAv, *ptr;

	newAv = malloc(sizeof(av));
	if (newAv == NULL)
	{
		fprintf(stderr, "Allocation Failed\n");
		return (NULL);
	}

	newAv->data = strdup(str);
	newAv->next = NULL;

	if (*head == NULL)
	{
		*head = newAv;
		return (newAv);
	}

	ptr = *head;
	while (ptr->next != NULL)
		ptr = ptr->next;

	ptr->next = newAv;

	return (ptr);
}

/**
 * free_av - frees a list.
 * @head: the linked list to be freed,
 *
 * Return: void.
*/
void free_av(av *head)
{
	if (head != NULL)
	{
		free_av(head->next);
		free(head->data);
		free(head);
	}
}
