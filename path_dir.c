#include "main.h"

/**
  * path_dir - builde a linked list to PATH environment Variable
  * @varname: head of the lnked list
  *
  *
  * Return:
  */
node_t *path_dir(char *varname)
{
	node_t *current;
	node_t *head;
	char *directories, *token;

	directories = getenv(varname);
	if (directories == NULL)
	{
		fprintf(stderr, "Variable not Found: %s\n", varname);
		return (NULL);
	}

	current = NULL;
	head = NULL;

	token = strtok(directories, ":");
	while (token != NULL)
	{
		node_t *newNode;

		newNode = (node_t*)malloc(sizeof(node_t));
		if (newNode == NULL)
		{
			perror("Failed to Allocate Memoery\n");
			exit(EXIT_FAILURE);
		}

		newNode->dir = strdup(token);
		if (newNode == NULL)
		{
			return (NULL);
		}
		newNode->node = NULL;

		if (head == NULL)
		{
			head = newNode;
		}
		else
		{
			current = head;
			while (current->node != NULL)
			{
				current = current->node;
			}
			current->node = newNode;
		}
		token = strtok(NULL, ":");
	}
	return (head);
}

