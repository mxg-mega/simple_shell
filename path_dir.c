#include "main.h"

/**
  * main - prints the directory that are in the PATH environment
  *
  * Return: always 0
  */
int main(void)
{
	printf("%s\n", _getenv("HOME"));
	return (0);
}
