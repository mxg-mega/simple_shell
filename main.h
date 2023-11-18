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
void handle_sigterm(int signum);
char *readInput(void);
void tokenizeInput(char *buffer, char **argv);

#endif/*MAIN_H*/
