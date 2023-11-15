#include "main.h"

/**
  * tokenizeInput - tokenizes the buffer
  *
  *
  *
  * Return:
  */
void tokenizeInput(char *buffer, char **argv)
{
	unsigned int i = 0;
	char *token, *delimiter = " ";

	token = strtok(buffer, delimiter);
	while (token != NULL)
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, delimiter);
	}
	argv[i] = NULL;
}
