#include "main.h"

/**
  * getBinaryPath - gets the binari path for the environment
  * @command: string for the command
  *
  * Return: pointer to a string of the binary path
  */
char *getBinaryPath(char *command)
{
	char *binary_path;
	int slashCount = 0;
	int argvl;

	for (argvl = 0; command[argvl] != '\0'; argvl++)
	{
		if (command[argvl] == '/')
		{
			slashCount++;
		}
	}

	if (slashCount > 0)
	{
		binary_path = command;
	}
	else
	{
		binary_path = searchInPath(command);
		if (binary_path == NULL)
		{
			perror("Command Not Found\n");
			free(binary_path);
			_exit(EXIT_FAILURE);
		}
	}

	return (binary_path);
}

