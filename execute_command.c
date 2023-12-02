#include "main.h"

/**
  * execute - function executes the command given
  * @binary_path: the binary path
  * @args: the arguments
  * @program: name of program
  *
  * Return: 0 if success and -1 if fail
  */
int execute(char *binary_path, char **args, char *program)
{
	pid_t child;

	child = fork();
	handle_child_fork(child);
	if (child == 0)
	{
		if (execve(binary_path, args, environ) == FAIL)
		{
			fprintf(stderr, "%s: No such file or directory\nbinaryPath: %s\n", program, binary_path);
			return (-1);
		}
		exit(EXIT_SUCCESS);
	}
	return (child);
}

