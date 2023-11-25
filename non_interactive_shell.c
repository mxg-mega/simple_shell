#include "main.h"

#define FAIL -1
#define BUFF_SIZE 1024
#define MAX_ARGS 2

char **initialize_args(char **args, char *token, char *buffer);
void free_args(char **args);
/**
  * non_interactive_shell - a simple shell
  * @program: program name
  *
  * Return: Always 0
  */
void non_interactive_shell(char *program, char *cmd)
{
	int status;
	ssize_t r;
	pid_t child;
	char *buffer, *token = NULL, *delimiters = " \n\t";

	buffer = malloc(BUFF_SIZE);
	if (buffer == NULL)
	{
		perror("Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}
	if (cmd != NULL)
	{
		strncpy(buffer, cmd, BUFF_SIZE - 1);
		buffer[BUFF_SIZE - 1] = '\0';
	}
	else
	{
		r = read(STDIN_FILENO, buffer, BUFF_SIZE);
		if (r == -1)
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
			char **args;
			
			args = initialize_args(args, token, buffer);

			strncpy(args[0], token, strlen(token));
			args[1] = NULL;
			if (execve(args[0], args, environ) == FAIL)
			{
				fprintf(stderr, "%s: No such file or directory\ncmd: %s\n", program, buffer);
				free(buffer);
				free(args);
				_exit(EXIT_FAILURE);
			}
			free(args);
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
  *
  *
  */
char **initialize_args(char **args, char *token, char *buffer)
{
	int i, tokenlen;

	args = (char **)malloc(sizeof(char *) * MAX_ARGS);
	if (args == NULL)
	{
		free(buffer);
		perror("Unable to allocate memory for args");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < (MAX_ARGS - 1); i++)
	{
		if (token != NULL)
		{
			tokenlen = strlen(token);
			args[i] = malloc(sizeof(char) * tokenlen);
			if (args[i] == NULL)
			{
				int j;

				for (j = 0; j < i; j++)
				{
					free(args[j]);
				}
				free(args);
				free(buffer);
				exit(EXIT_FAILURE);
			}
		}
		else
		{

			args[i] = malloc(sizeof(char *));
			if (args[i] == NULL)
			{
				int j;

				for (j = 0; j < i; j++)
				{
					free(args[j]);
				}
				free(buffer);
				free(args);
				exit(EXIT_FAILURE);
			}
		}
	}
	return (args);
}

void free_args(char **args)
{
	int i;

	for (i = 0; i < MAX_ARGS; i++)
	{
		free(args[i]);
	}
	free(args);
}

