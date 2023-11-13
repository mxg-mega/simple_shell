#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFF_SIZE 1024
#define MAX_ARGS 64
#define FAIL -1

extern char **environ;

typedef struct node
{
	char *dir;
	struct node *node;
} node_t;

char* readInput(void);
void tokenizeInput(char* buffer, char* delimiter, char** argv);
char* getBinaryPath(char* command);
char *searchInPath(char *command);
char *_getenv(const char *name);
ssize_t _getline(char **buffer, size_t *nbyte, FILE *fd);
char *_strtok(char *input, char *delimiter);
node_t *path_dir(char *varname);

#endif/*MAIN_H*/
