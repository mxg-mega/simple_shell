#include "main.h"

/**
  * main - prints the address of the implementation
  * of the two enviroment variables
  *
  * Return: Always 0
  */
int main(int ac, char **av, char **env)
{
	extern char **environ;

	printf("main - env: %p\nGlobal var - environ: %p\n", *env, *environ);
	return (0);
}
