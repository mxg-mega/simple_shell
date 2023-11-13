#include "main.h"

/**
  * main - reads a line from input stream
  *
  * Return; always 0
  */
int main(void)
{
	char *buffer;
	size_t buff_size = 1024;
	ssize_t read;

	buffer = malloc(buff_size * sizeof(char));
	if (buffer == NULL)
	{
		perror("failed to allocate memory\n");
		exit(1);
	}
	printf("$ ");
	read = _getline(&buffer, &buff_size, stdin);
	if (read == -1)
	{
		perror("Error reading line\n");
		exit(98);
	}
	printf("%s", buffer);
	free(buffer);
	return (0);
}

