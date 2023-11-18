#include "main.h"

/**
  * readInput - Read input from the user
  *
  * Return: a string
  */
char *readInput(void)
{
	char *buffer;
	size_t buff_size = 1024;

	buffer = malloc(sizeof(char) * buff_size);
	if (buffer == NULL)
	{
		perror("unable to allocate memory\n");
		return (NULL);
	}
	if (fgets(buffer, buff_size, stdin) == NULL)
	{
		free(buffer);
		exit(EXIT_FAILURE);
	}

	return (buffer);
}

