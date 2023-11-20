#include "main.h"

#define FAIL -1

/**
  * handle_sigterm - function handles the termination signal
  * @signum: signal for termination
  *
  * Return: no return
  *
void handle_sigterm(int signum)
{
	if (signum == SIGTERM)
	{
		exit(EXIT_SUCCESS);
	}
}
*/
/**
  * handle_child_fork - function handles child process
  * @child: the return of child process
  *
  * Return: no Return
  */
void handle_child_fork(pid_t child)
{
	if (child == -1)
	{
		perror("child process creation failed\n");
		_exit(EXIT_FAILURE);
	}
}

/**
  * main - a simple shell
  * @ac: number of arguments
  * @av: argument variable array
  *
  * Return: Always 0
  */
int main(int __attribute__ ((unused)) ac, char **av)
{
	int status;
	char *buffer = NULL;

	do
	{
		pid_t child;

		prompt("#cisfun$");
		buffer = readInput();
		child = fork();
		handle_child_fork(child);
		if (child == 0)
		{
			char *args[2];

			args[0] = buffer;
			args[1] = NULL;
			if (execve(buffer, args, NULL) == -1)
			{
			fprintf(stderr, "%s: No such file or directory\n", av[0]);
			free(buffer);
			_exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (waitpid(child, &status, 0) == -1)
			{
				free(buffer);
				exit(EXIT_FAILURE);
			}
		}
	} while (1);

	return (0);
}

