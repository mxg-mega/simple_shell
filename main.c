#include "main.h"

/**
  * main - entry point
  * @ac: argument count
  * @av: argument array
  *
  * Return: Always 0
  */
int main(int ac __attribute__ ((unused)), char **av)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
	{
		interactive_shell(av[0]);
	}
	else
	{
		non_interactive_shell(av[0]);
	}
	return (0);
}

