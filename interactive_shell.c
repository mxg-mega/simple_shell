#include "main.h"

#define FAIL -1

/**
  * interactive_shell - interactive mode
  * @program: the program name
  *
  * Return: Always 0
  */
void interactive_shell(char *program)
{
	int status;
	char *input;
	pid_t child;

	while (!feof(stdin))
	{
		prompt("#cisfun$");
		input = readInput();
		child = fork();
		handle_child_fork(child);
		if (child == 0)
		{
			char *args[2];

			args[0] = input;
			args[1] = NULL;
			if (execve(input, args, NULL) == -1)
			{
				fprintf(stderr, "%s: No such file or directory\n", program);
				free(input);
				_exit(EXIT_FAILURE);
			}
			free(input);
		}
		else
		{
			if (waitpid(child, &status, 0) == -1)
			{
				free(input);
				exit(EXIT_FAILURE);
			}
			free(input);
		}
	}
}
