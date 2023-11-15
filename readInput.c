#include "main.h"

/**
  * readInput - function reads the command
  * @buffer: the buffer
  * @buffsize: size of buffer
  *
  * Return: a string of the command
  */
char *readInput(char *buffer, size_t buffsize)
{
	size_t read, bufflen;

	if (buffer == NULL || buffsize == 0)
	{
		return (NULL);
	}
	read = getline(&buffer, &buffsize, stdin);
	if (read == (size_t)FAIL)
	{
		free(buffer);
		_exit(EXIT_FAILURE);
	}
	bufflen = strlen(buffer);
	buffer[bufflen - 1] = '\0';

	return(buffer);
}
