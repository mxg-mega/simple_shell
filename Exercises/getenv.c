#include "main.h"

/**
  * _getenv - gets a specific environment variable
  * @name: the variable to get
  *
  * Return: a pointer to the string
  */
char *_getenv(const char *name)
{
	char **env = environ;
	unsigned int i;
	size_t k = strlen(name);

	for (i = 0; env[i] != NULL; i++)
	{
		int j;

		if (strncmp(name, env[i], k) == 0)
		{
			j = 0;
			while (env[i][j] != '\0')
			{
				if (env[i][j] == '=')
				{
					return (&env[i][j + 1]);
				}
				j++;
			}
		}
	}

	fprintf(stderr, "Variable not found: %s\n", name);
	return (NULL);
}

