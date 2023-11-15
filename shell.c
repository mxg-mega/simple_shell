#include "main.h"

#define FAIL -1

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

	while (1)
	{
		char *buffer, *argv[] = {NULL};

		child = fork();
		if (child == -1)
		{
			perror("child process creation failed\n");
			exit(EXIT_FAILURE);
		}
		if (child == 0)
		{
			buffer = malloc(sizeof(char) * buffsize);
			if (buffer == NULL)
			{
				perror("Failed to allocate memory\n");
				_exit(EXIT_FAILURE);
			}
			printf("#cisfun $ ");
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

