#include "main.h"

/**
  * readInput - Read input from the user
  *
  * Return: a string
  */
char *readInput(void)
{
	char *buffer = NULL;
	size_t buff_size = 0;
	size_t read;

	printf("#cisfun $ ");

	fflush(stdin);
	read = getline(&buffer, &buff_size, stdin);
	if (read == (size_t)FAIL)
	{
		/*perror("Unable to read from input stream\n");*/
		free(buffer);
		exit(EXIT_FAILURE);
	}

	return (buffer);
}

