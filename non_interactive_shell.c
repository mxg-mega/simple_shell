#include "main.h"

#define FAIL -1
#define BUFF_SIZE 1024

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
	char *buffer, *token;

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
	token = strtok(buffer, "\n");
	while (token != NULL){
		child = fork();
		handle_child_fork(child);
		if (child == 0)
		{
			char **args;

			args = malloc(sizeof(char *) * 2);
			if (args == NULL)
			{
				perror("Unable to allocate memory for args\n");
				free(buffer);
				_exit(EXIT_FAILURE);
			}
			args[0] = token;
			args[1] = NULL;
			if (execve(args[0], args, environ) == FAIL)
			{
				fprintf(stderr, "%s: No such file or directory\ncmd: %s\n", program, buffer);
				free(buffer);
				_exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, "\n");
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