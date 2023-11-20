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
	int read;

	read = getline(&buffer, &buff_size, stdin);
	if (read == FAIL)
	{
		if (feof(stdin))
		{
			free(buffer);
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(buffer);
			exit(EXIT_FAILURE);
		}
	}

	buffer[strcspn(buffer, "\n")] = '\0';
	return (buffer);
}

