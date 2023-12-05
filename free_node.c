#include "main.h"

/**
  * free_node - deletes an entire list
  * @head: head node of list
  * Return: no return
  */
void free_node(node_t *head)
{
	if (head == NULL)
	{
		return;
	}
	free_node(head->node);
	free(head->dir);
	free(head);
}
