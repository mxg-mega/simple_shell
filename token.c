#include "main.h"

/**
  * main - prints token strings
  *
  * Return: always 0
  */
int main(void)
{
	char input[] = "apple banana cherry mah mj k uio f jyfyj ghv hb jhvfx yfh vjvj";
	char delimiter[] = " ";
	char *token;

	token = _strtok(input, delimiter);
    while (token != NULL)
    {
        printf("Token: %s\n", token);
        token = _strtok(NULL, delimiter);
    }
	return (0);
}

