#include "main.h"

/**
  * main - a super simple shell
  *
  * Return: Always 0
  */
int main(void)
{
	pid_t child;
	int status;

	while (1)
	{
		char *buffer, *delimiter = " ";
		char *binary_path;
		char *argv[MAX_ARGS + 1] = {NULL};

		child = fork();
		if (child == FAIL)
		{
			perror("Unable to create a Child Process\n");
			exit(EXIT_FAILURE);
		}
		if (child == 0)
		{
			buffer = readInput();
			if (strcmp(buffer, "exit") == 0)
			{
				free(buffer);
				exit(EXIT_SUCCESS);
			}
			tokenizeInput(buffer, delimiter, argv);

			binary_path = getBinaryPath(argv[0]);

			if (execve(binary_path, argv, NULL) == FAIL)
			{
				perror("Unable to execute command\n");
				free(buffer);
				exit(EXIT_FAILURE);
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

