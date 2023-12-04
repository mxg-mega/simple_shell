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
#define MAX_ARGS 64
#define BUFF_SIZE 1024
#define MAX_TOKEN_LENGTH 200

extern char **environ;

typedef struct command
{
	char *command;
	struct command *nextCmd;
}cmd_t;


cmd_t *addCommandNode(cmd_t **head, const char *newCommand);
int countNode(cmd_t *head);
char *get_next_line(char *buffer);
int countArgs(char *cmd);
void free_list(cmd_t *head);
void nonInteractiveMode(void);

char *_strtok(char *input, char *delimiter);

void prompt(char *text);
void non_interactive_shell(char *program, char *cmd);
void interactive_shell(char *program);
void handle_child_fork(pid_t child);
char *readInput(void);
void tokenizeInput(char *buffer, char **argv);
char *searchInPath(char *command);
char *getBinaryPath(char *command);
int execute(char *binary_path, char **args, char *program);
/*char **initialize_args(char **args);*/
void free_args(char **args, int memsize);
void set_args_elements(char **args, char *token, int pos);
int countLines(char *buffer, char *delimiters);

#endif/*MAIN_H*/
