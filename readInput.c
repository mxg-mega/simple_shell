#include "main.h"

/**
  * Read input from the user
  */
char* readInput(void)
{
	char *buffer;
	size_t buff_size = 1024;
	size_t read, bufflen;

	buffer = malloc(sizeof(char) * buff_size);if (buffer == NULL)
	{
		perror("failed to allocate memory");
		exit(EXIT_FAILURE);
	}

	printf("#cisfun $ ");
	read = getline(&buffer, &buff_size, stdin);

	if (read == (size_t)FAIL)
	{
		perror("Unable to read from input stream\n");
		exit(EXIT_FAILURE);
	}

	bufflen = strlen(buffer);
	buffer[bufflen - 1] = '\0';

	return (buffer);
}

