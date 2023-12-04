#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void display_prompt() {
    printf("simple_shell$ ");
    fflush(stdout);
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        display_prompt();

        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle Ctrl+D (EOF)
            printf("\n");
            break;
        }

        // Remove newline character at the end
        input[strcspn(input, "\n")] = '\0';

        // Fork a child process
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            // Execute the command
            if (execlp(input, input, (char *)NULL) == -1) {
                // Print error if executable is not found
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            // Wait for the child process to complete
            waitpid(pid, &status, 0);

            // Check if the child process exited successfully
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                fprintf(stderr, "Error: Command not found\n");
            }
        }
    }

    printf("Exiting shell...\n");

    return 0;
}
