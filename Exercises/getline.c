#include "main.h"

/**
  * _getline - reads the characters from the input stream
  * @buffer: the string
  * @nbyte: the number of to read
  * @fd: where to get them
  *
  * Return: return the number of characters read
  */
ssize_t _getline(char **buffer, size_t *nbyte, FILE *fd)
{
	char readchar;
	ssize_t count = 0;
	size_t size = 0;

	if (!*buffer || !*nbyte)
	{
		return (-1);
	}
	for (count = 0; (readchar = fgetc(fd)) != EOF && readchar != '\n'; count++)
	{
		if (count >= (ssize_t)size - 1)
		{
			char *temp;

			size = *nbyte + 3;
			temp = (char *)realloc(*buffer, size);
			if (temp == NULL)
			{
				return (-1);
			}
			*buffer = temp;
			*nbyte = size;
		}
		(*buffer)[count] = (char)readchar;
	}

	if (count == 0 && readchar == EOF)
	{
		free(buffer);
		return (-1);
	}

	(*buffer)[count++] = '\n';
	(*buffer)[count] = '\0';
	return (count);
}

