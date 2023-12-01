#include "main.h"

#define FAIL -1
#define BUFF_SIZE 1024
#define MAX_ARGS 64
#define MAX_TOKEN_LENGTH 200

char **initialize_args(char **args);
void free_args(char **args);
void set_args_elements(char **args, char *token, int pos);

/**
  * non_interactive_shell - a simple shell
  * @program: program name
  * @cmd: command
  *
  * Return: Always 0
  */
void nonInteractive_shell(char *program, char *cmd)
{
	int status, child, lineNum, i;
	ssize_t r;
	char *buffer, *token = NULL, *delimiters = "\n";
	char *argsLines[] = {NULL};
	char **args;

	buffer = malloc(BUFF_SIZE);
	if (buffer == NULL)
	{
		perror("Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}
	memset(buffer, 0, BUFF_SIZE);
	if (cmd != NULL)
	{
		strncpy(buffer, cmd, BUFF_SIZE - 1);
		buffer[BUFF_SIZE - 1] = '\0';
	}
	else if (cmd == NULL)
	{
		r = read(STDIN_FILENO, buffer, BUFF_SIZE);
		if (r == (ssize_t)FAIL)
		{
			perror("Could not read command\n");
			free(buffer);
			exit(EXIT_FAILURE);
		}
		if (buffer == NULL)
		{
			free(buffer);
			_exit(EXIT_SUCCESS);
		}
		buffer[BUFF_SIZE - 1] = '\0';
	}
	token = strtok(buffer, delimiters);
	lineNum = 0;
	while (token != NULL)
	{
		argsLines[lineNum] = token;
		lineNum++;
		token = strtok(NULL, delimiters);
	}
	argsLines[lineNum] = NULL;

	for (i = 0; argsLines[i] != NULL; i++)
	{
		args = initialize_args(args);
		if (args == NULL)
		{
			exit(EXIT_FAILURE);
		}
		tokenizeInput(argsLines[i], args);
		if (buffer == NULL || args[0] == NULL)
		{
			_exit(EXIT_SUCCESS);
		}
		if ((child = execute(args[0], args, program)) == FAIL)
		{
			exit(EXIT_FAILURE);
		}
		free_args(args);
	}
	if (child > 0)
	{
		if (waitpid(child, &status, WUNTRACED) == -1)
		{
			free(buffer);
			exit(EXIT_FAILURE);
		}
	}
}

/**
  * initialize_args - function initializes args
  *
  * Return: a pointer to the array of strings
  */
char **initialize_args(char **args)
{
	int i;

	args = malloc(sizeof(char *) * MAX_ARGS + 1);
	if (args == NULL)
	{
		perror("Unable to allocate memory for args\n");
		return (NULL);
	}
	for (i = 0; i < MAX_ARGS; i++)
	{
		args[i] = NULL;
	}
	args[MAX_ARGS - 1] = NULL;
	return (args);
}

void set_args_elements(char **args, char *token, int pos)
{
	if (token != NULL)
	{
		args[pos] = strdup(token);
	}
}

/**
  * free_args - function frees the memory of args
  * @args: the 2d array
  * Return: no return
  */
void free_args(char **args)
{
	int i;

	for (i = 0; i < MAX_ARGS; i++)
	{
		free(args[i]);
	}
	free(args);
}

