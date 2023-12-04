#include "main.h"


void nonInteractiveMode(char *program)
{
	char *buffer, *delimiters = " \n";
	size_t buffsize = (size_t)BUFF_SIZE;
	pid_t child;
	cmd_t *head = NULL, *current = NULL;

	buffer = malloc(sizeof(char) * buffsize);
	if (buffer == NULL)
	{
		exit(EXIT_FAILURE);
	}
	memset(buffer, 0, buffsize);

	while (fgets(buffer, buffsize, stdin))
	{
		printf("%s", buffer);
		addCommandNode(&head, buffer);
	}

	current = head;
	while (current != NULL)
	{
		char *dup, *token;
		int i = 0;
		char **args;

		args = initialize_args(args);
		if (args == NULL)
		{
			free_args(args, MAX_ARGS);
			break;
		}
		dup = strdup(current->command);
		if (dup == NULL)
		{
			break;
		}
		token = strtok(dup, delimiters);
		while (token != NULL)
		{
			printf("token[%s]\n", token);
			set_args_elements(args , token, i);
			i++;
			token = strtok(NULL, delimiters);
		}
		if (args[0] == NULL)
		{
			free(token);
			free(dup);
			free_args(args, i);
			break;
		}
		if ((child = execute(args[0], args, program)) == -1)
		{
			free(dup);
			free(token);
			free_args(args, i);
			break;
		}
		printf("%s, %d\n", current->command, countArgs(current->command));
		current = current->nextCmd;
		free(dup);
		free(token);
		free_args(args, i);
	}
	printf("%d\n", countNode(head));

	if (child > 0)
	{
		int status;

		if (waitpid(child, &status, 0) == -1)
		{
			free(buffer);
			free_list(head);
			exit(EXIT_FAILURE);
		}
		free_list(head);
		free(buffer);
	}
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

