#include "main.h"

/**
  * getBinaryPath - gets the binary path for the environment
  * @command: string for the command
  *
  * Return: pointer to a string of the binary path
  */
char *getBinaryPath(char *command)
{
	char *binary_path;
	int slashCount = 0;
	int argvl;

	if (command == NULL)
	{
		return (NULL);
	}
	for (argvl = 0; command[argvl] != '\0'; argvl++)
	{
		if (command[argvl] == '/')
		{
			slashCount++;
		}
	}

	if (slashCount > 0)
	{
		binary_path = strdup(command);
	}
	else
	{
		binary_path = searchInPath(command);
		if (binary_path == NULL)
		{
			perror("Command Not Found\n");
			free(binary_path);
			return (NULL);
		}
		else
		{
			return (binary_path);
		}
	}

	free(binary_path);
	return (NULL);
}

