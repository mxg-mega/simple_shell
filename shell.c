#include "main.h"

#define MAX_ARGS 64
#define FAIL -1

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

	while (1)
	{

		char *buffer, *delimiter = " ", *token;
		char *binary_path;
		int argvl;
		unsigned int i, bufflen, slashCount = 0;
		char *argv[MAX_ARGS + 1] = {NULL};

		child = fork();
		if (child == FAIL)
		{
			perror("Unable to create a Child Process\n");
			exit(EXIT_FAILURE);
		}
		if (child == 0)
		{
			buffer = malloc(sizeof(char) * buff_size);
			if (buffer == NULL)
			{
				perror("failed to allocate memory");
				exit(EXIT_FAILURE);
			}
			printf("#cisfun $ ");
			read = getline(&buffer, &buff_size, stdin);
			if (read == (size_t)FAIL)
			{
				perror("Unable to read from input stream\n");
				exit(EXIT_FAILURE);
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

			for(argvl = 0; argv[0][argvl] != '\0'; argvl++)
			{
				if (argv[0][argvl] == '/')
				{
					slashCount++;
				}
			}
			if (slashCount > 0)
			{
				
				if (argv[0][0] == '/')
				{
					binary_path = argv[0];
				}
				else
				{
					binary_path = argv[0];
				}
			}
			else
			{
				binary_path = searchInPath(argv[0]);
				if (binary_path == NULL)
				{
					perror("Command Not Found\n");
					exit(EXIT_FAILURE);
				}
			}
			if (execve(binary_path, argv, NULL) == FAIL)
			{
				perror("Unable to execute command\n");
				free(buffer);
				exit(EXIT_FAILURE);
			}
			free(buffer);
			return (0);
		}
		else
		{
			waitpid(child, &status, 0);
		}
	}
	return (0);
}

