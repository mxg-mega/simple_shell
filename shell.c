#include "main.h"

size_t read_command(char **buffer, size_t *nbyte, FILE *fd)
{
	ssize_t getCommand;

	getCommand = getline(buffer, nbyte, fd);
	if (getCommand == -1)
	{
		perror("Error reading line\n");
		exit(98);
	}

	(*buffer)[strlen(*buffer) - 1] = '\0';

	return (getCommand);
}
/**
  * run - runs the shell by reading and executing
  *
  * Return: non yet
  */
void run()
{
	char *buffer;
	size_t nbyte = BUFF_SIZE;
	pid_t execute;
	size_t cl;

	buffer = malloc(sizeof(char) * BUFF_SIZE);
	if (buffer == NULL)
	{
		perror("failed to allocate memory\n");
		exit(1);
	}
	printf("#cisfun $ ");

	cl = read_command(&buffer, &nbyte, stdin);

	if (cl > 0)
	{
		char *argv[] = {buffer, NULL};

		if ((execute = execve(argv[0], argv, NULL)) == -1)
		{
			perror("failed to Execute command\n");
			exit(99);
		}
	}
}
/**
  * main - Super Simple shell
  * 
  * Return: Always 0
  */
int main(void)
{
	run();
	return (0);
}

