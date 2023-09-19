#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

/**
 * struct path - for path handling
 * @length: string length
 * @path: string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct _path
{
    int length;
	char *path;
	struct _path *next;
} _path;

extern char **environ;

int _putchar(char c);
int _intractive_checker (int argc);
char *command_getter (_path *now);
void command_excuter (char **command_arg, char **enviroment, int *exit_st, _path *now, char **argv);
_path *extract_directories();
char *_strdup(char *str);
int _strlen(char *s);
_path *add_node(_path **head, const char *str);
int letter_counter(char *str, char c);
void free_list(_path *head);
char **command_arg_getter(char *command, int exit_st);
char *command_maker(char *first_com, char *command, char **com_arg, int exit_st);
char **commands_getter(int active, char *prog, char *file);
int _strcmp(char *s1, char *s2);
char *itos(int pid);
void error_handler(char **command_arg, char **enviroment, int *exit_st, _path *now, char **argv);
char *check_access(char *line_av_1, _path *current);
#endif
