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

#define BUFF_SIZE 1024
#define MAX_ARGS 64
#define FAIL -1

extern char **environ;

char *readInput(char *buffer, size_t bufferlen);
void tokenizeInput(char *buffer, char **argv);

#endif/*MAIN_H*/
