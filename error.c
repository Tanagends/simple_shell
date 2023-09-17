#include "zimbo.h"
/**
 * err_cd - displays invalid directory cd.
 * @toks: cd command.
 */
void err_cd(char **toks)
{
	char err[300] = "";

	switch (errno){
		case (ENOENT):
			_strcpy(err, global_argv[0]);
			_strcat(err, ": ");
			_strcat(err, toks[1]);
			_strcat(err, ": No such file or directory");
			write(STDOUT_FILENO, err, strlen(err));
			write(STDOUT_FILENO, "\n", 1);
			break;
		case (EACCES):
			_strcpy(err, global_argv[0]);
			_strcat(err, ": ");
			_strcat(err, " cd: ");
			_strcat(err, toks[1]);
			_strcat(err, ": Permission denied");
	}
	return;
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
	write(STDOUT_FILENO, err, strlen(err));
	write(STDOUT_FILENO, "\n", 1);
	return;
}
