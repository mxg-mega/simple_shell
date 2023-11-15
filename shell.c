#include "main.h"

#define FAIL -1

sig_atomic_t exit_request = 0;

/**
  * handle_sigterm - handles the termination signal
  * @signum: the signal number
  *
  * Return; void
  */
void handle_sigterm(int signum)
{
	if (signum == SIGTERM)
	{
		exit_request = 1;
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
	size_t buffsize = 1024;
	int status;

	signal(SIGTERM, handle_sigterm);
	while (!exit_request)
	{
		char *buffer, *argv[] = {NULL};

		child = fork();
		if (child == -1)
		{
			perror("child process creation failed\n");
			_exit(EXIT_FAILURE);
		}
		if (child == 0)
		{
			buffer = malloc(sizeof(char) * buffsize);
			if (buffer == NULL)
			{
				perror("Failed to allocate memory\n");
				_exit(EXIT_FAILURE);
			}
			printf("#cisfun$ ");
			buffer = readInput(buffer, buffsize);
			argv[0] = buffer;
			argv[1] = NULL;
			if (execve(argv[0], argv, NULL) == -1)
			{
				fprintf(stderr, "%s: No such file or directory\n", av[0]);
				_exit(EXIT_FAILURE);
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

