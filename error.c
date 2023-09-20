#include "zimbo.h"

void err_perm(char **toks, char **argv);

/**
 * err_cd - displays invalid directory cd.
 * @toks: cd command.
 * @i: error.
 * @global_argv: shell arguments.
 */
void err_cd(char **toks, int i, char **global_argv)
{
	char err[300] = "";
	struct stat dir;

	stat(toks[1], &dir);
	if (i == 4 || i == 2)
		return;
	if (S_ISDIR(dir.st_mode) && (access(toks[1], R_OK)))
	{
		err_perm(toks, global_argv);
		return;
	}
	if (!S_ISDIR(dir.st_mode))
	{
		if (isatty(STDIN_FILENO))
		{
			_strcpy(err, global_argv[0]);
			_strcat(err, ": ");
			_strcat(err, toks[1]);
			_strcat(err, ": No such file or directory");
			write(STDOUT_FILENO, err, _strlen(err));
			write(STDOUT_FILENO, "\n", 1);
		}
		else
		{
			_strcpy(err, global_argv[0]);
			_strcat(err, ": 1: cd: can't cd to ");
			_strcat(err, toks[1]);
			write(STDERR_FILENO, err, _strlen(err));
			write(STDERR_FILENO, "\n", 1);
		}
	}
}

/**
 * err_env - displays excess env arguments error
 * @toks: - env
 */
void err_env(char **toks)
{
	char err[300] = "";

	_strcpy(err, "env: '");
	_strcat(err, toks[1]);
	_strcat(err, "': No such file or directory");
	write(STDOUT_FILENO, err, _strlen(err));
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * err_perm - displays permission errors for dir.
 * @toks: tokenized input.
 * @argv: shell armuments.
 */
void err_perm(char **toks, char **argv)
{
	char err[300] = "";

	if (isatty(STDIN_FILENO))
	{
		_strcpy(err, argv[0]);
		_strcat(err, ": ");
		_strcat(err, " cd: ");
		_strcat(err, toks[1]);
		_strcat(err, ": Permission denied");
		write(STDOUT_FILENO, err, _strlen(err));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		_strcpy(err, argv[0]);
		_strcat(err, ": 1: cd: can't cd to ");
		_strcat(err, toks[1]);
		write(STDERR_FILENO, err, _strlen(err));
		write(STDERR_FILENO, "\n", 1);
	}
}
/**
 * exit_shell - shuts off the shell
 * @input: user input.
 * @toks: tokenized input.
 */
void exit_shell(char *input, char **toks)
{
	int exit_status;
	char err[300] = "./hsh: 1: exit: Illegal number: ";

	if (toks[1] != NULL)
	{
		exit_status = atoi(toks[1]);
		if (exit_status > 0)
		{
			free(toks);
			free(input);
			exit(exit_status);
		}
		else if (exit_status == 0 && _strcmp(toks[1], "0") == 0)
		{
			free(toks);
			free(input);
			exit(0);
		}
		else if (((exit_status == 0) && (_strcmp(toks[1], "0") != 0)) ||
				exit_status < 0)
		{
			_strcat(err, toks[1]);
			_strcat(err, "\n");
			write(STDERR_FILENO, err, _strlen(err));
			free(toks);
			free(input);
			exit(2);
		}
	}
}
