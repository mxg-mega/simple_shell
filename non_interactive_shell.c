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
	}
	else
	{
		size_t bufflen;

		r = read(STDIN_FILENO, buffer, BUFF_SIZE);
		if (r == -1)
		{
			perror("Could not read command\n");
			free(buffer);
			exit(EXIT_FAILURE);
		}
		bufflen = strlen(buffer);
		buffer[bufflen - 1] = '\0';
	}
	token = strtok(buffer, "\n");
	while (token != NULL){
		child = fork();
		handle_child_fork(child);
		if (child == 0)
		{
			char *args[2];

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
