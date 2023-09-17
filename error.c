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
			strcpy(err, global_argv[0]);
			strcat(err, ": ");
			strcat(err, toks[1]);
			strcat(err, ": No such file or directory");
			write(STDOUT_FILENO, err, strlen(err));
			write(STDOUT_FILENO, "\n", 1);
			break;
		case (EACCES):
			strcpy(err, global_argv[0]);
			strcat(err, ": ");
			strcat(err, " cd: ");
			strcat(err, toks[1]);
			strcat(err, ": Permission denied");
	return;
}
/**
 * err_env - displays excess env arguments error
 * @toks: - env
 */
void err_env(char **toks)
{
	char err[300] = "";

	strcpy(err, "env: '");
	strcat(err, toks[1]);
	strcat(err, "': No such file or directory");
	write(STDOUT_FILENO, err, strlen(err));
	write(STDOUT_FILENO, "\n", 1);
	return;
}
