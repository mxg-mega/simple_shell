#include "main.h"

#define FAIL -1
#define BUFF_SIZE 1024
#define MAX_ARGS 64
#define MAX_TOKEN_LENGTH 200

void free_args(char **args, int memsize);
void set_args_elements(char **args, char *token, int pos);

/**
  * non_interactive_shell - a simple shell
  * @program: program name
  * @cmd: command
  *
  * Return: Always 0
  */
void non_interactive_shell(char *program, char *cmd)
{
	int status, child;
	ssize_t r;
	char *buffer, *token = NULL, *delimiters = "\n";

	buffer = malloc(BUFF_SIZE);
	if (buffer == NULL)
	{
		perror("Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}
	memset(buffer, 0, BUFF_SIZE);

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

	if (cmd == NULL)
	{
		printf("%s\n", buffer);
	}
	token = strtok(buffer, delimiters);
	while (token != NULL)
	{
		char *arg_token = NULL, *del = " \t\n";
		char *binary_path = NULL;
		char **args;
		int i;

		args = initialize_args(args);
		if (args == NULL)
		{
			free_args(args, MAX_ARGS);
			free(buffer);
			_exit(EXIT_FAILURE);
		}
		arg_token = strtok(token, del);
		i = 0;
		while (arg_token != NULL && i < MAX_ARGS)
		{
			set_args_elements(args, arg_token, i);
			i++;
			arg_token = strtok(NULL, del);
		}
		set_args_elements(args, NULL, i);
		if (args[0] == NULL)
		{
			free(buffer);
			free(binary_path);
			free_args(args, MAX_ARGS);
			_exit(EXIT_SUCCESS);
		}

		binary_path = strdup(args[0]);
		if (args[0] != NULL)
		{
			if ((child = execute(binary_path, args, program)) == -1)
			{
				free(buffer);
				free_args(args, MAX_ARGS);
				free(binary_path);
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delimiters);
		free_args(args, MAX_ARGS);
		free(binary_path);
	}

	if (child > 0)
	{
		if (waitpid(child, &status, 0) == -1)
		{
			free(buffer);
			exit(EXIT_FAILURE);
		}
		free(buffer);
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
	args = malloc(sizeof(char *) * (MAX_ARGS + 2));

	if (args == NULL)
	{
		perror("Unable to allocate memory for args\n");
		return (NULL);
	}
	for (i = 0; i <= MAX_ARGS; i++)
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

