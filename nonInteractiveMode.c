#include "main.h"

void trimWhitespaces(char *str);

/**
  * nonInteractiveMode - function allows the interpreter to execute multiple commands
  * @program: name of the shell
  * Return: no return
 */
void nonInteractiveMode(char *program)
{
	char *buffer = NULL, *delimiters = " \n";
	size_t buffsize = (size_t)BUFF_SIZE;
	pid_t child = 0;
	cmd_t *head = NULL, *current = NULL;

	buffer = malloc(sizeof(char) * buffsize);
	if (buffer == NULL)
	{
		exit(EXIT_FAILURE);
	}
	memset(buffer, 0, buffsize);

	while (fgets(buffer, buffsize, stdin))
	{
		trimWhitespaces(buffer);
		if (buffer[0] == '\0')
		{
			continue;
		}
		printf("%s", buffer);

		if (addCommandNode(&head, buffer) == NULL)
		{
			free(buffer);
			exit(EXIT_FAILURE);
		}
	}

	current = head;
	while (current != NULL)
	{
		char *dup = NULL, *token = NULL, *binary_path = NULL;
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
			free_args(args, MAX_ARGS);
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
		if ((binary_path = searchInPath(args[0])) == NULL)
		{
			free(dup);
			free_args(args, MAX_ARGS);
			break;
		}
		if ((child = execute(binary_path, args, program)) == -1)
		{
			free(dup);
			free_args(args, MAX_ARGS);
			break;
		}
		printf("%s, %d\n", current->command, countArgs(current->command));
		current = current->nextCmd;
		free(dup);
		free(binary_path);
		free_args(args, MAX_ARGS);
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
	free(buffer);
	free_list(head);
	exit(EXIT_SUCCESS);
}

/**
  * countArgs - function counts the number of lines read by the systemcall read
  * @cmd: the command that is the buffer
  * Return: the number of lines or 0 if failed
 */
int countArgs(char *cmd)
{
	char *token = NULL;
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
	cmd_t *current = NULL;
	int count = 0;

	current = head;
	while (current != NULL)
	{
		count++;
		current = current->nextCmd;
	}
	return (count);
}

/**
 * trimWhitespaces - trims leading and trailing whitespaces in place
 * @str: the string to trim
 */
void trimWhitespaces(char *str)
{
	int start = 0, end = 0, len = 0, i = 0;

	if (str == NULL)
	{
		return;
	}
	len = strlen(str);
	for (start = 0; start < len && isspace((unsigned char)str[start]); start++)
		;

	if (start == len)
	{
		str[0] = '\0';
		return;
	}

	for (end = len - 1; end >= 0 && isspace((unsigned char)str[end]); end--)
		;

	for (i = 0; i <= end - start; i++)
		str[i] = str[start + i];

	str[end - start + 2] = '\0';
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

