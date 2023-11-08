#include "main.h"

/**
  * _strtok - custom strtok method which tokenizes a string
  * @input: the string to delimit
  * @delimiter: the delimiter
  *
  * Return: a pointer to the tokenized string
  */
char *_strtok(char *input, char *delimiter)
{
	static char *last;
	char *token;
	size_t i;

	if (input != NULL)
	{
		last = input;
	}
	else if (last == NULL)
	{
		return (NULL);
	}

	token = last;
	i = 0;
	while (last[i] != '\0')
	{
		size_t k;

		k = 0;
		while (delimiter[k] != '\0' && last[i + k] == delimiter[k])
		{
			k++;
		}
		if (k == strlen(delimiter))
		{
			last[i] = '\0';
			i += k;
			last = &last[i];
			return (token);
		}
		i++;
	}

	if (last[i] != '\0')
	{
		last[i] = '\0';
		i++;
		last = &last[i];
	}
	else
	{
		last = NULL;
	}
	return (token);
}

