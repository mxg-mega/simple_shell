#include "main.h"

/**
  * _getenv - gets a specific environment variable
  * @name: the variable to get
  *
  * Return: a pointer to the string
  */
char *_getenv(const char *name)
{
	extern char **environ;
	unsigned int i, match = 0;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(name, environ[i], strlen(name)) == 0)
		{
			match = 1;
			break;
		}
	}
	if (match != 1)
	{
		printf("Not found\n");
		return (NULL);
	}
	printf("Working\n");
	return (environ[i]);
}

