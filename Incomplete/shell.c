#include "main.h"

/**
  * handle_sigterm - this function handles the signal to terminate
  * @signum: the termination signal
  *
  * Return: no return
  */
void handle_sigterm(int signum)
{
	if (signum == SIGTERM)
	{
		exit_requested = 1;
	}
}

/**
  * check_for_exit - function checks if the input is "exit"
  * @buffer: the input
  *
  * Return: no return
  */
void check_for_exit(char *buffer)
{
	if (strcmp(buffer, "exit") == 0)
	{
		free(buffer);
		kill(0, SIGTERM);
		_exit(EXIT_SUCCESS);
	}
}

/**
  * main - a super simple shell
  *
  * Return: Always 0
  */
int main(void)
{
	pid_t child;
	int status;

	signal(SIGTERM, handle_sigterm);
	while (!exit_requested)
	{
		char *buffer, *delimiter = " ", *binary_path;
		char *argv[] = {NULL};

		child = fork();
		if (child == FAIL)
		{
			perror("Unable to create a Child Process\n");
			_exit(EXIT_FAILURE);
		}
		if (child == 0)
		{
			buffer = readInput();
			check_for_exit(buffer);
			tokenizeInput(buffer, delimiter, argv);
			if (argv[0] == NULL)
			{
				_exit(EXIT_FAILURE);
			}
			binary_path = getBinaryPath(argv[0]);
			if (execve(binary_path, argv, NULL) == FAIL)
			{
				perror("Unable to execute command\n");
				free(buffer);
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

