#include "main.h"

#define FAIL -1
#define MAX_COMMAND_LENGTH 100

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
	char input[MAX_COMMAND_LENGTH];
	pid_t child;

	do
	{
		prompt("#cisfun$");
		if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		child = fork();
		handle_child_fork(child);
		if (child == 0)
		{
			char *args[2];

			args[0] = input;
			args[1] = NULL;
			if (execve(input, args, NULL) == -1)
			{
			fprintf(stderr, "%s: No such file or directory\n", av[0]);
			_exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (waitpid(child, &status, 0) == -1)
			{
				exit(EXIT_FAILURE);
			}
		}
	} while (1);

	return (0);
}

