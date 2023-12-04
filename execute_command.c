#include "main.h"

/**
  * execute - function executes the command given
  * @binary_path: the binary path
  * @args: the arguments
  * @program: name of program
  *
  * Return: 0 if success and -1 if fail
  */
int execute(char *binary_path, char **args, char *program)
{
	pid_t child;

	child = fork();
	if (child == FAIL)
	{
		perror("Failed to create child process\n");
		return (FAIL);
	}
	if (child == 0)
    {
        /* Child process */
        if (execve(binary_path, args, environ) == FAIL)
        {
            fprintf(stderr, "%s: No such file or directory\n", program);
            return (FAIL);
        }
    }
    else
    {
        /* Parent process */
        int status;

        if (waitpid(child, &status, 0) == FAIL)
        {
            perror("Waitpid failed");
            return (FAIL);
        }

        /* Check if the child process terminated normally */
        if (WIFEXITED(status))
        {
            /* Return the exit status of the child process */
            return (WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            /* If the child process was terminated by a signal, print the signal number */
            fprintf(stderr, "%s: Terminated by signal %d\n", program, WTERMSIG(status));
        }
        else
        {
            /* Some other unexpected condition */
            fprintf(stderr, "%s: Unexpected termination\n", program);
        }
    }

    return (FAIL);
}

