#include "main.h"

/**
  * tokenizeInpute - Tokenize the input string
  * @buffer: the string to tokenize
  * @delimiter: the delimiter
  * @argv: array to hold the tokens
  *
  * Return: no Return
  */
void tokenizeInput(char* buffer, char* delimiter, char** argv)
{
	char *token;
	unsigned int i;

	token = strtok(buffer, delimiter);
	for (i = 0; token != NULL && i < MAX_ARGS; i++)
	{
		argv[i] = token;
		token = strtok(NULL, delimiter);
	}
	argv[i] = NULL;
}
