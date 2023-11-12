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
	unsigned int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(name, environ[i], strlen(name)) == 0){
			int j;

			j = 0;
			while (environ[i][j] != '\0'){
				if (environ[i][j] == '=')
				{
					return (&environ[i][++j]);
				}
				j++;
			}
		}
	}
	return (NULL);
}

