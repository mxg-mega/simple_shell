#include "main.h"

/**
  * tokenizeInput - tokenizes the buffer
  * @buffer: the string
  * @argv: the execution array of arguments
  *
  * Return: no return
  */
void tokenizeInput(char *buffer, char **argv)
{
	unsigned int i = 0;
	char *token, *delimiter = " \n\t";

	token = strtok(buffer, delimiter);
	while (token != NULL)
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, delimiter);
	}
	argv[i] = NULL;
}
