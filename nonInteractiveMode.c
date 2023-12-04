#include "main.h"


void nonInteractiveMode(void)
{
	char *buffer; /* , *token, *delimiters = "\n"; */
	size_t buffsize = (size_t)BUFF_SIZE;
/*	int inputStatus;*/
	cmd_t *head = NULL, *current = NULL;

	buffer = malloc(sizeof(char) * buffsize);
	if (buffer == NULL)
	{
		exit(EXIT_FAILURE);
	}
	memset(buffer, 0, buffsize);

	while (fgets(buffer, buffsize, stdin))
	{
		printf("%s\n", buffer);
		addCommandNode(&head, buffer);
	}
/*	inputStatus = read(STDIN_FILENO, buffer, buffsize);
	if (inputStatus == FAIL)
	{
		free(buffer);
		exit(EXIT_FAILURE);
	}
	if (buffer == NULL)
	{
		free(buffer);
		exit(EXIT_SUCCESS);
	}
	buffer[buffsize - 1] = '\0';
	bufflen = strlen(buffer);
	printf("%s\n%ld\n", buffer, bufflen);

	token = _strtok(buffer, delimiters);
	while (token != NULL)
	{
		addCommandNode(&head, token);
		token = _strtok(NULL, delimiters);
	}
*/
	current = head;
	while (current != NULL)
	{
		printf("%s, %d\n", current->command, countArgs(current->command));
		current = current->nextCmd;
	}
	printf("%d\n", countNode(head));

	free_list(head);
	free(buffer);
}

int countArgs(char *cmd)
{
	char *token;
	int i = 0;

	if (cmd == NULL)
	{
		return (0);
	}
	token = strtok(cmd, " \t\n");
	while (token != NULL)
	{
		i++;
		token = strtok(NULL, " \t\n");
	}
	return (i);
}

int countNode(cmd_t *head)
{
	cmd_t *current;
	int count = 0;

	current = head;
	while (current != NULL)
	{
		count++;
		current = current->nextCmd;
	}
	return (count);
}

