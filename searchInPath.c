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
	char *token, *delim = ":";
	struct stat fileInfo;

	if (command == NULL)
	{
		perror("command is null\n");
		return (NULL);
	}
	token = strtok(path, delim);
	while (token != NULL)
	{
		char *filepath = malloc(strlen(token) + strlen(command) + 2);
		if (filepath == NULL)
		{
			return (NULL);
		}

		sprintf(filepath, "%s/%s", token, command);

		printf("%s\n", filepath);
		if (access(filepath, X_OK) == 0 && stat(filepath, &fileInfo) == 0)
		{
			return (filepath);
		}
		free(filepath);
		token = strtok(NULL, delim);
	}
	return (NULL);
}

