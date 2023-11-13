#include "main.h"

/**
  * main - the third prototype of main
  *
  * Return: Always 0
  */
int main(int ac, char **av, char **env)
{
	/* This implementation uses the main parameter char **env */

	unsigned int i;

	for (i = 0; env[i] != NULL; i++)
	{
		printf("%s\n", env[i]);
	}
	/*
	   This is the implementation to print the environment variables using
	   Environ
	extern char **environ;
	unsigned int i = 0;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	 */
	return (0);
}
