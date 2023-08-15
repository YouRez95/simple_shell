#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


struct Node {
	char *data;
	struct Node *next;
};

typedef struct Node av;

void add_at_end(av **head,  const char *token);
void free_av(av *head);

int main(void)
{
	char *buffer = NULL;
	size_t n = 0;
	av *head, *ptr;
	char **argvs = NULL;
	int i;
	int j;

	printf("myShell $ -> ");
	while(getline(&buffer, &n, stdin) != -1)
	{
		i = 0;
		j = 0;
		/*  Remove the new line from the buffer */
		while(buffer[i] != '\0')
		{
			if(buffer[i]  == '\n')
				buffer[i] = '\0';
			i++;
		}
		/* split the buffer in chunks with delimeter " " and calcul how much strings we have in the command */
		i = 0;
		char *token = strtok(buffer, " ");
		while (token != NULL)
		{
			/* add the node in the end of linked list */
			add_at_end(&head, token);
			token = strtok(NULL, " ");
			i++;
		}

		/* allocate memory for the array of strings (pointers) + NULL*/
		argvs = malloc((i + 2) * sizeof(char *));
		if (argvs == NULL)
		{
			fprintf(stderr, "memory allocation failed\\n");
			return (1);
		}

		/* allocate memory for each string and copy the strings to the array */
		ptr = head;
		for (j = 0; j < i; j++)
		{
			argvs[j] = malloc(strlen(ptr->data) * sizeof(char));
			if (argvs == NULL)
			{
				fprintf(stderr, "allocation memory failed\n");
				return (1);
			}
			strcpy(argvs[j], ptr->data);
			ptr = ptr->next;
		}

		/* Test Execution */
		pid_t child_pid = fork();
		if  (child_pid == 0)
		{
			execve(argvs[0], argvs, NULL);
			return (1);
		}

		/* just for printing the element of array */
		printf("array of strings: \n");
		for (j = 0; j <= i; j++)
		{
			printf("argvs[%d] = %s\n", j, argvs[j]);
			free(argvs[j]);
		}

		/* free the linked list */
		free_av(head);
		argvs = NULL;
		head = NULL;
		printf("myShell $ -> ");

	}
	return 0;
}

void add_at_end(av **head,  const char *token)
{
	av *newAv = malloc(sizeof(av));
	av *ptr;

	if (newAv == NULL)
	{
		fprintf(stderr, "Allocation Failed\n");
		return;
	}

	newAv->data = strdup(token);
	newAv->next = NULL;

	if (*head == NULL)
	{
		*head = newAv;
		return;
	}

	ptr = *head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = newAv;
}

void free_av(av *head)
{
	av *current = head;
	av *nextAv;
	while(current != NULL)
	{
		nextAv = current->next;
		free(current->data);
		free(current);
		current = nextAv;
	}
}
