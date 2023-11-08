#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - fork & wait & execve exercise
 *
 * Return: Always 0.
 */
int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	pid_t child;
	int i;
	int status;

	for (i = 5; i > 0; i--)
	{
		child = fork();
		if (child == -1)
		{
			perror("child process failed\n");
			return (1);
		}
		if (child == 0)
		{
			if ((execve(argv[0], argv, NULL) == -1))
			{
				perror("Error: failed to execute\n");
			}
			sleep(3);
			exit(-1);
		}
	}
	for (i = 0; i < 5; i++)
	{
		pid_t exited_child;

		exited_child = wait(&status);
		printf("\nChild process %d done\n", exited_child);
	}
	return (0);
}

