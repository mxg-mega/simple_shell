#include "main.h"

cmd_t *addCommandNode(cmd_t **head, const char *newCommand)
{
	cmd_t *current;
	cmd_t *newNode;

	if (newCommand == NULL)
	{
		return (NULL);
	}
	newNode = malloc(sizeof(cmd_t));
	if (newNode == NULL)
	{
		return (NULL);
	}
	newNode->command = strdup(newCommand);
	newNode->nextCmd = NULL;

	if (*head == NULL)
	{
		*head = newNode;
		return (*head);
	}
	current = *head;
	while (current->nextCmd != NULL)
	{
		current = current->nextCmd;
	}
	current->nextCmd = newNode;
	return (*head);
}

