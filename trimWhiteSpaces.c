#include "main.h"

/**
  * trimWhitespace - Function to trim leading and trailing whitespaces from a string
  * @str: the string
  *
  * Return: a new string with leading and trailing whitespaces removed
  * NULL if the input string is NULL or empty after trimming
*/
char *trimWhitespace(char *str)
{
	size_t start = 0, length;
	size_t end = strlen(str) - 1;
	char *trimmedStr;

    if (str == NULL)
    {
	    return (NULL);
    }
    /* Find the index of the first non-whitespace character */
    while (isspace((unsigned char)str[start]))
    {
        start++;
    }

    /* Find the index of the last non-whitespace character */
    while (end > start && isspace((unsigned char)str[end]))
    {
        end--;
    }

    /* Calculate the length of the trimmed string */
    length = (end >= start) ? (end - start + 1) : 0;

    /* Allocate memory for the trimmed string */
    trimmedStr = malloc(length + 1);
    if (trimmedStr == NULL)
    {
        /* Memory allocation failure */
	return (NULL);
    }

    /* Copy the trimmed portion to the new string */
    strncpy(trimmedStr, str + start, length);
    /* Null-terminate the trimmed string */
    trimmedStr[length] = '\0';

    return (trimmedStr);
}

