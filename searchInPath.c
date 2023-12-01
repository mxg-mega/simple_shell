#include "main.h"

/**
  * searchInPath - searches for a command in the path variable
  * @command: a string conatining the command
  *
  * Return: string of the directory
  */
char *searchInPath(char *command)
{
	char *path = getenv("PATH");
	char *token, *delim = " :\n", *file = NULL;
	int slashCount = 0;
	struct stat fileInfo;

	if (command == NULL)
	{
		perror("command is null\n");
		return (NULL);
	}
	if (command[0] == '/')
	{
		file = strdup(command);
		return (file);
	}
	else
	{
		int i;

		for (i = 0; command[i] != '\0'; i++)
		{
			if (command[i] == '/')
			{
				slashCount++;
			}
		}
	}

	if (slashCount == 0)
	{
		token = strtok(path, delim);
		while (token != NULL)
		{
			char *filepath = malloc(strlen(token) + strlen(command) + 2);
			if (filepath == NULL)
			{
				perror("Unable to Allocate Memory for filepath\n");
				return (NULL);
			}

			sprintf(filepath, "%s/%s", token, command);

			printf("%s\n", filepath);
			if (access(filepath, X_OK) == 0 && stat(filepath, &fileInfo) == 0)
			{
				file = strdup(filepath);
				free(filepath);
				break;
			}
			free(filepath);
			token = strtok(NULL, delim);
		}
	}
	else
	{
		free(file);
		return (strdup(command));
	}
	return (file);
}

