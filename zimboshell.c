#include "zimbo.h"
/**
 * main - a simple shell
 * Return: 0(Always success).
 */
/* double free error*/
/* error messages*/
/* executing a command only on the first prompt*/
char **global_argv;
int main(int argc, char *argv[])
{
	char *input = NULL, **toks = NULL;
	size_t size = 0;
	ssize_t k = 0;
	int status = 1, i;

	global_argv = argv;
	(void) argc;
	signal(SIGINT, SIG_IGN);
	while (status)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "Zimboshell$ ", 12);
		/*if (i != -1)*/
	/*	{*/
		k = getline(&input, &size, stdin);
		/*	if (k != -1)*/
		/*	{*/
		/*k = _getline(&input, &size, STDIN_FILENO);*/
		if (k == -1)
		{
			if (input != NULL)
				free(input);
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (-1);
		}
		toks = zimbo_split(input);
		status = zimbo_execute(toks);
		free(toks);
	}
	free(input);
	return (0);
}
/**
 * zimbo_split - tokenize string.
 * @string: string to be tokenized.
 *
 * Return: tokenized string.
 */
char **zimbo_split(char *string)
{
	char *tok;
	size_t count = 0;
	char **toks = malloc(MAX_LINE * sizeof(char *));

	if (!toks)
	{
		perror("Malloc Error");
		exit(errno);
	}
	tok = strtok(string, ZIMBO_DELIM);
	while (tok != NULL)
	{
	toks[count++] = tok;
		tok = strtok(NULL, ZIMBO_DELIM);
	}
	toks[count] = NULL;
	return (toks);
}
/**
 * zimbo_execute - executes commands
 * @toks: token to a pointer
 * Return: 1 (Success)
 */
int zimbo_execute(char **toks)
{
	pid_t _pid;
	int i, status, builtins = -1, path = 0;
	/*char *path_handler = NULL, path_handler_backup[MAX_LINE] = "";*/
	
	for (i = 0; toks [i] != NULL; i++)
	{
	if (_strcmp(toks, "#") == 0)
	{
		handle_comments(toks[i]);
		}
	else if (_strcmp(toks, ";") == 0)
	{
		if (toks[i + 1] != NULL)
	{
		handle_colon(toks[i + 1]);
	}
	i++;
	}
}
	if (toks[0] == NULL)
		return (1);
	if (access(toks[0], X_OK) == 0)
	{
		zim_exec(toks[0], toks);
		return (1);
	}
	builtins = zimbo_builtins(toks);
	if (builtins != -1)
		return (builtins);
	path = zimbo_path__handler(toks);
	if (path == 0)
		errmsg(toks, global_argv);
	return (1);
}
/**
 * zim_exec - runs command.
 * @execfile: executable file.
 * @arguments: parameters
 */
void zim_exec(char *execfile, char **arguments)
{
	pid_t _pid;
	int status/*, i*/;

	_pid = fork();
	if (_pid == 0)/* Now in the child */
	{
		execve(execfile, arguments, environ);
		perror("execve error!");
		return;
	}
	else if (_pid > 0)/* Now in the parent */
		wait(&status);
	else
		perror("fork error");
	return;
}
/**
 * zimbo_path__handler - handles the path
 * @toks: token given
 * Return: Found path.
 */
int zimbo_path__handler(char **toks)
{
	char *path_token, *path_copy, *path, full_path[300] = "";
	int i, fd;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
	}
	if (path)
		path_copy = _strdup(path);
	if (environ[i] != NULL)
	{
		path_token = strtok(path_copy, ":");
		while (path_token != NULL)
		{
			_strcpy(full_path, path_token);
			_strcat(full_path, "/");   /* Append a forward slash*/
			_strcat(full_path, toks[0]); /* Append 'command'*/
			fd = access(full_path, X_OK);
			if (fd == 0)
			{
				zim_exec(full_path, toks);
				free(path_copy);
				return (1);
			}
			path_token = strtok(NULL, ":");
		}
	}
	free(path_copy);
	return (0);
}
/**
 * zimbo_builtins - checks and execute builtins.
 * @toks: tokenized string.
 * Return: 1
 */
int zimbo_builtins(char **toks)
{
	int i;
	char *builtstr[] = {"cd", "setenv", "env", "exit", "unsetenv"};
	typedef int (*Builtfunc)(char **);
	Builtfunc builtfunc[5] = {zimbo_cd,
				zimbo_setenv,
				zimbo_env,
				zimbo_exit,
				zimbo_unset_env};

	for (i = 0; i < 5; i++)
	{
		if (_strcmp(builtstr[i], toks[0]) == 0)
			return ((*builtfunc[i])(toks));
	}
	return (-1);
}
