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

ssize_t _getline(char **buffer, size_t *nbyte, FILE *fd);
char *_strtok(char *input, char *delimiter);

#endif/*MAIN_H*/
