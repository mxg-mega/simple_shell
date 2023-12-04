#include "main.h"

/**
  * main - prints the address of the implementation
  * of the two enviroment variables
  *
  * Return: Always 0
  */
int main(int __attribute__ ((unused)) ac, char __attribute__ ((unused)) **av, char **env)
{
	printf("main - env: %p\nGlobal var - environ: %p\n", *env, *environ);
	return (0);
}
