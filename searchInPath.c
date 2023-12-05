#include "main.h"

/**
  * searchInPath - searches for a command in the path variable
  * @command: a string conatining the command
  *
  * Return: string of the directory
  */
char *searchInPath(char *command)
{
	node_t *path = path_dir("PATH");
	char *file = NULL;
	int slashCount = 0;
	struct stat fileInfo;

	if (command == NULL)
	{
		perror("command is null\n");
		free_node(path);
		return (NULL);
	}
	if (command[0] == '/')
	{
		file = strdup(command);
		if (file == NULL)
		{
			free_node(path);
			return (NULL);
		}
		free_node(path);
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
		node_t *current = NULL;

		current = path;
		while (current->node != NULL)
		{
			char *dir_dup = strdup(current->dir);
			char *filepath = malloc(strlen(current->dir) + strlen(command) + 2);

			if (filepath == NULL || dir_dup == NULL)
			{
				perror("Unable to Allocate Memory for filepath or dir_dup\n");
				free_node(path);
				return (NULL);
			}
			sprintf(filepath, "%s/%s", dir_dup, command);
			printf("%s\n", filepath);
			if (access(filepath, X_OK) == 0 && stat(filepath, &fileInfo) == 0)
			{
				file = strdup(filepath);
				if (file == NULL)
				{
					free(filepath);
					free(dir_dup);
					free_node(path);
					return (NULL);
				}
				free(filepath);
				free(dir_dup);
				break;
			}
			free(filepath);
			free(dir_dup);
			current = current->node;
		}
	}
	else
	{
		free(file);
		free_node(path);
		return (command);
	}
	free_node(path);
	return (file);
}

