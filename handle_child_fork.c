#include "main.h"

/**
  * handle_child_fork - handles the child process
  * @child: pid of child
  *
  * Return: no return
  */
void handle_child_fork (pid_t child)
{
	if (child == -1)
	{
		perror("Child process creation Failed\n");
		exit(EXIT_FAILURE);
	}
}
