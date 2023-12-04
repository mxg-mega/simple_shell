#include "main.h"

#define FAIL -1
#define BUFF_SIZE 1024
#define MAX_ARGS 64
#define MAX_TOKEN_LENGTH 200

char **initialize_args(char **args);
void free_args(char **args, int memsize);
void set_args_elements(char **args, char *token, int pos);
int countLines(char *buffer, char *delimiters);

/**
  * non_interactive_shell - a simple shell
  * @program: program name
  * @cmd: command
  *
  * Return: Always 0
  */
void nonInteractive_shell(char *program, char *cmd)
{
	int lineNum, k, j;
	/*int child, status, j;*/
	ssize_t r;
	char *buffer, *token, *delimiters = "\n";
	char **argsLines;
	/*char **args; */

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

	printf("%s\n", buffer);
	lineNum = countLines(buffer, delimiters);
	argsLines = malloc(sizeof(char *) * (lineNum + 1));
	if (argsLines == NULL)
	{
		free(buffer);
		exit(EXIT_FAILURE);
	}

	for (j = 0; j <= lineNum; j++)
	{
		argsLines[j] = NULL;
	}

	k = 0;
	token = strtok(buffer, delimiters);
	while (token != NULL)
	{
		argsLines[k] = strdup(token);
		if (argsLines == NULL)
		{
			perror("Failed to duplicate token\n");
			break;
		}
		k++;
		printf("%s, %d\n", token, k);
		token = strtok(NULL, delimiters);
	}
	argsLines[k] = NULL;

	printf("%s, %d\n", program, lineNum);
	free_args(argsLines, lineNum);
	free(buffer);
	/*for (i = 0; argsLines[i] != NULL; i++)
	{
		args = initialize_args(args);
		if (args == NULL)
		{
			perror("Failed to allocate memory\n");
			free(buffer);
			free_args(args, MAX_ARGS);
			free_args(argsLines, lineNum);
			exit(EXIT_FAILURE);
		}

		tokenizeInput(argsLines[i], args);

		if (args[0] != NULL)
		{
			if ((child = execute(args[0], args, program)) == FAIL)
			{
				perror("Execution failed\n");
				free(buffer);
				free_args(argsLines, lineNum);
				free_args(args, MAX_ARGS);
				exit(EXIT_FAILURE);
			}

			printf("%s\n", argsLines[i]);
		}
		free_args(args, MAX_ARGS);
	}
	printf("%d\n", lineNum);
	if (child > 0)
	{
		if (waitpid(child, &status, WUNTRACED) == -1)
		{
			free(buffer);
			free_args(argsLines, lineNum);
			exit(EXIT_FAILURE);
		}
		free(buffer);
		free_args(argsLines, lineNum);
	}*/
}

int countLines(char *buffer, char *delimiters)
{
	int lineNum;
	char *token = NULL;

	if (buffer == NULL || delimiters == NULL)
	{
		perror("Buffer or delimiters are NULL\n");
		return (0);
	}
	token = strtok(buffer, delimiters);
	lineNum = 0;
	while (token != NULL)
	{
		lineNum++;
		token = strtok(NULL, delimiters);
	}
	return (lineNum);
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

	return (args);
}

void set_args_elements(char **args, char *token, int pos)
{
	if (token != NULL)
	{
		args[pos] = strdup(token);
	}
	else
	{
		args[pos] = NULL;
	}
}

/**
  * free_args - function frees the memory of args
  * @args: the 2d array
  * Return: no return
  */
void free_args(char **args, int memsize)
{
	int i;

	for (i = 0; i < memsize; i++)
	{
		free(args[i]);
	}
	free(args);
}

