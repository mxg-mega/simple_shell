#include "main.h"

int main(void)
{
	node_t *head;

	head = path_dir("PATH");
	while (head->node != NULL)
	{
		printf("%s\n", head->dir);
		head = head->node;
	}
	printf("===========\nDONE\n");
	return (0);
}
