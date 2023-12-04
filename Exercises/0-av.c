#include <stdio.h>

/**
  * main - print all arguments
  *
  * Return: always 0
  */
int main(int ac, char **av)
{
	int i;

	for (i = 0; i < ac; i++)
	{
		printf("argument[%d]: %s\n", i, av[i]);
	}
	printf("Total number of arguments printed: %d\n", i);
	return (0);
}

