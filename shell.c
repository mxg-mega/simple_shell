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
void handle_child_fork(pid_t child, char *buffer)
{
	if (child == -1)
	{
		perror("child process creation failed\n");
		free(buffer);
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
	int terminate = 0;

	while (terminate == 0)
	{
		char *buffer;
		char *argv[] = {NULL};

		buffer = readInput();
		if (buffer == NULL)
		{
			break;
		}

		child = fork();
		handle_child_fork(child, buffer);
		if (child == 0)
		{
			if (buffer != NULL)
			{
				argv[0] = buffer;
				argv[1] = NULL;
				if (argv[0] == NULL)
				{
					free(buffer);
					_exit(EXIT_FAILURE);
				}
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
			wait(NULL);
			free(buffer);
		}
	}
	return (0);
}

