#ifndef ZIMBO_H
#define ZIMBO_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#define MAX_LINE 2048
#define ZIMBO_DELIM " \t\r\n\a"

/* Global variables */
extern char **environ;
extern char **global_argv;
ssize_t _getline(char **lineptr, size_t *n, int fd);
int zimbo_path__handler(char **toks);
char **zimbo_split(char *string);
int zimbo_execute(char **toks, char **argv);
int zimbo_cd(char **toks, char **argv);
int zimbo_env(char **toks);
int zimbo_setenv(char **toks);
int zimbo_exit(char **toks);
int zimbo_builtins(char **toks);
int zimbo_unset_env(char **toks);
void set_old_new_pwd(char *pwd, char *nwd);
int handle_cd(char **toks);
int cd_home(void);
char *_memset(char *s, char b, unsigned int n);
int _strncmp(const char *s1, const char *s2, size_t n);
int _strcmp(const char *s1, const char *s2);
void zim_exec(char *execfile, char **arguments);
void errmsg(char **command, char **global_argv);
char *_strtok(char *string, const char *delimiters);
int delim(char *token, const char *lim);
void *_memchr(char *buffer, char c, ssize_t n);
void err_cd(char **toks, int i, char **global_argv);
void err_env(char **toks);
void err_home(char **global_argv);
void *_memcpy(void *dest, const void *src, size_t n);
size_t _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strdup(char *str);
int handle_commands(char *input);
void end(char *input);
int errr(char *input);


/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct alis_t
{
	char *str;
	unsigned int len;
	struct alis_t *next;
} alist;
alist *add_node_end(alist **head, const char *name, const char *alis);
void free_list(alist *head);

typedef int (*Builtfunc[])(char **toks);

#endif
