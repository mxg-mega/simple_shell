#include "main.h"

#define FAIL -1

/**
  * handle_sigterm - function handles the termination signal
  * @signum: signal for termination
  *
  * Return: no return
  */
void handle_sigterm(int signum)
{
	if (signum == SIGTERM)
	{
		exit(EXIT_SUCCESS);
	}
}

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
	pid_t child;
	int status;

	signal(SIGTERM, handle_sigterm);
	while (1)
	{
		char *buffer;

		child = fork();
		handle_child_fork(child);
		if (child == 0)
		{
			buffer = readInput();

			if (buffer != NULL)
			{
				char *argv[] = {NULL};

				tokenizeInput(buffer, argv);
				if (execve(argv[0], argv, NULL) == -1)
				{
					fprintf(stderr, "%s: No such file or directory\n", av[0]);
					free(buffer);
					_exit(99);
				}
			}
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(child, &status, 0);
		}
	}
	return (0);
}

