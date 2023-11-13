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
	char *token;
	char *filepath;
	struct stat *fileInfo;

	if (command == NULL)
	{
		perror("No Command Entered\n");
		return (NULL);
	}
	token = strtok(path, ":");
	while (token != NULL)
	{
		filepath = strcat(token, command);
		if (stat(filepath, &fileInfo) == 0)
		{
			return (filepath);
		}
		token = strtok(NULL, ":");
	}
	perror("Executable not Found\n");
	return (NULL);
}

