#include "main.h"

#define MAX_ARGS 64

/**
  * main - a super simple shell
  *
  * Return: Always 0
  */
int main(void)
{

	size_t read, buff_size = 1024;
	pid_t child;
	int status;

	while (1){

		char *buffer, *delimiter = " ", *token;
		unsigned int i, bufflen;
		char *argv[MAX_ARGS + 1] = {NULL};

		child = fork();
		if (child == -1)
		{
			perror("Unable to create a Child Process\n");
			exit(98);
		}
		if (child == 0)
		{
			buffer = malloc(sizeof(char) * buff_size);
			if (buffer == NULL)
			{
				perror("failed to allocate memory");
				exit(1);
			}
			printf("#cisfun $ ");
			read = _getline(&buffer, &buff_size, stdin);
			if (read == -1)
			{
				perror("Unable to read from input stream\n");
				exit(3);
			}

			bufflen = strlen(buffer);
			buffer[bufflen - 1] = '\0';

			token = strtok(buffer, delimiter);
			for (i = 0; token != NULL && i < MAX_ARGS; i++)
			{
				argv[i] = token;
				token = strtok(NULL, delimiter);
			}
			argv[i] = NULL;
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("Unable to execute command\n");
				exit(2);
			}
			free(buffer);
			exit(4);
		}
		else
		{
			waitpid(child, &status, 0);
		}
		free(buffer);
	}
	return (0);
}

