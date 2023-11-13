#include "main.h"

/**
  * main - entry point checks for the existance of a file
  * in the current path
  *
  * Return: always 0
  */
int main(int ac, char **av)
{
	struct stat sta;
	int i;

	if (ac < 2)
	{
		perror("No File Name Found\n");
		exit(98);
	}
	for (i = 1; av[i]; i++)
	{
		if (stat(av[i], &sta) == -1)
		{
			printf("File Not Found\n");
		}
		else
		{
			printf("File Found\n");
		}
	}
	return (0);
}
