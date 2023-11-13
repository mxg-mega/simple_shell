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
	char *token, *filepath;
	struct stat fileInfo;

	if (command == NULL)
	{
		perror("No Command Entered\n");
		return (NULL);
	}
	token = strtok(path, ":");
	while (token != NULL)
	{
		int pathlen;

		pathlen = strlen(command) + strlen(token) + 2;
		filepath = malloc(pathlen);
		snprintf(filepath, pathlen, "%s/%s", token, command);

		if (stat(filepath, &fileInfo) == 0 && fileInfo.st_mode & S_IXUSR)
		{
			return (filepath);
		}
		free(filepath);
		token = strtok(NULL, ":");
	}
	perror("Executable not Found\n");
	return (NULL);
}

