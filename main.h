#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FAIL -1

extern char **environ;

void prompt(char *text);
void non_interactive_shell(char *program, char *cmd);
void interactive_shell(char *program);
void handle_child_fork(pid_t child);
char *readInput(void);
void tokenizeInput(char *buffer, char **argv);
char *searchInPath(char *command);
char *getBinaryPath(char *command);
int execute(char *binary_path, char **args, char *program);

#endif/*MAIN_H*/
