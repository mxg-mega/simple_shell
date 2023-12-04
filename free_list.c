#include "main.h"

/**
  * free_list - deletes an entire list
  * @head: head node of list
  * Return: no return
  */
void free_list(cmd_t *head)
{
	if (head == NULL)
	{
		return;
	}
	free_list(head->nextCmd);
	free(head->command);
	free(head);
}
