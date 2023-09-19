#include "zimbo.h"
/**
 * main - a simple shell
 * @argc: argument count.
 * @argv: argument parameter list.
 * Return: 0(Always success).
 */
int main(int argc, char *argv[])
{
	char *input = NULL, **toks = NULL;
	size_t size = 0;
	ssize_t k = 0;
	int status = 1;

	(void) argc;
	signal(SIGINT, SIG_IGN);
	while (status)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "Zimboshell$ ", 12);
		k = getline(&input, &size, stdin);
		/*if (handle_commands(input))*/
		/*{*/
		/*	handle_commands(input);*/
		/*	continue;*/
		/*}*/
		/*k = _getline(&input, &size, STDIN_FILENO);*/
		if (k == -1)
			end(input);
		toks = zimbo_split(input);
		status = zimbo_execute(toks, argv);
		free(toks);
		if (!isatty(STDIN_FILENO) && (status == 127))
			return (errr(input));
	}
	free(input);
	return (status);
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
 * @argv: main's arguments
 * Return: 1 (Success)
 */
int zimbo_execute(char **toks, char **argv)
{
	int builtins = -1, path = 0;

	if (toks[0] == NULL)
		return (1);
	if (access(toks[0], X_OK) == 0)
	{
		zim_exec(toks[0], toks);
		return (1);
	}
	if (strcmp(toks[0], "cd") == 0)
		return (zimbo_cd(toks, argv));
	builtins = zimbo_builtins(toks);
	if (builtins != -1)
		return (builtins);
	path = zimbo_path__handler(toks);
	if (path == 0)
	{
		errmsg(toks, argv);
		return (127);
	}
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
	int status, ex_status/*, i*/;

	_pid = fork();
	if (_pid == 0)/* Now in the child */
	{
		execve(execfile, arguments, environ);
		perror("execve error!");
	}
	else if (_pid > 0)/* Now in the parent */
	{
		waitpid(_pid, &status, 0);
		if (WIFEXITED(status))
		{
			ex_status = WEXITSTATUS(status);
			if ((ex_status == 2) && !isatty(STDOUT_FILENO))
				exit(2);
		}
	}
	else
		perror("fork error");
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
