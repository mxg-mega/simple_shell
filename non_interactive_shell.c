#include "main.h"

#define FAIL -1
#define BUFF_SIZE 1024
#define MAX_ARGS 64
#define MAX_TOKEN_LENGTH 200

char **initialize_args(void);
void free_args(char **args);
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
	int status;
	ssize_t r;
	pid_t child;
	char *buffer, *token = NULL, *delimiters = "\n\t";

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
	else
	{
		r = read(STDIN_FILENO, buffer, BUFF_SIZE);
		if (r == (ssize_t)FAIL)
		{
			perror("Could not read command\n");
			free(buffer);
			exit(EXIT_FAILURE);
		}
		buffer[BUFF_SIZE - 1] = '\0';
	}
	token = strtok(buffer, delimiters);
	while (token != NULL)
	{
		child = fork();
		handle_child_fork(child);
		if (child == 0)
		{
			char *arg_token = NULL, *del = " \t\n";
			char **args;
			int i = 0;

			args = initialize_args();
			arg_token = strtok(token, del);
			while (arg_token != NULL && i < MAX_ARGS)
			{
				set_args_elements(args, arg_token, i);
				i++;
				arg_token = strtok(NULL, del);
			}

			if (execve(args[0], args, environ) == FAIL)
			{
				fprintf(stderr, "%s: No such file or directory\n",
						program);
				free(buffer);
				free_args(args);
				_exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delimiters);
	}
	if (child > 0)
	{
		if (waitpid(child, &status, 0) == -1)
		{
			exit(EXIT_FAILURE);
			free(buffer);
		}
		free(buffer);
	}
}

/**
  * initialize_args - function initializes args
  *
  * Return: a pointer to the array of strings
  */
char **initialize_args(void)
{
	int i;
	char **args = malloc(sizeof(char *) * MAX_ARGS + 1);

	if (args == NULL)
	{
		perror("Unable to allocate memory for args\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < MAX_ARGS; i++)
	{
		args[i] = NULL;
	}
	/*
	for (i = 0; i < MAX_ARGS; i++)
	{
		if (token != NULL)
		{
			args[i] = strdup(token);
			if (args[i] == NULL)
			{
				free_args(args);
				perror("Unable to allocate memory for argument");
				exit(EXIT_FAILURE);
			}
		}
		else
		{

			args[i] = malloc(MAX_TOKEN_LENGTH);
			if (args[i] == NULL)
			{
				free_args(args);
				perror("Unable to allocate memory for argument");
				exit(EXIT_FAILURE);
			}
		}
	}*/
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

