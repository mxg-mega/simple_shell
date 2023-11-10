#include "main.h"

/**
  * main - a super simple shell
  *
  * Return: Always 0
  */
int main(void)
{
	int i;

	i = 0;
	while (i != 1){
		size_t read, buff_size = 1024;
		pid_t child;
		int status;

		child = fork();
		if (child == -1)
		{
			perror("Unable to create a Child Process\n");
			exit(98);
		}
		if (child == 0)
		{
			char *buffer, *delimiter = " ", *token;
			unsigned int i;
			char *argv[] = {NULL};

			printf("child\n");
			buffer = malloc(sizeof(char) * buff_size);
			if (buffer == NULL)
			{
				perror("failed to allocate memory");
				exit(1);
			}
			printf("$ ");
			read = _getline(&buffer, &buff_size, stdin);
			if (read == -1)
			{
				perror("Unable to read from input stream\n");
				exit(3);
			}

			token = strtok(buffer, delimiter);
			for (i = 0; token != NULL; i++)
			{
				argv[i] = token;
				token = strtok(NULL, delimiter);
			}
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("Unable to execute command\n");
				exit(2);
			}
			free(buffer);
			sleep(6);
			exit(4);
		}
		else
		{
			waitpid(child, &status, 0);
		}
	}
	return (0);
}

