#include "zimbo.h"
/**
 * err_home - displays home error
 * @global_argv: shell arguments.
 */
void err_home(char **global_argv)
{
	char buffer[300] = "";

	_strcpy(buffer, global_argv[0]);
	_strcat(buffer, ": cd: HOME not set");
	write(STDOUT_FILENO, buffer, strlen(buffer));
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * errmsg - displays error message.
 * @command: command entered.
 * @global_argv: argv.
 */
void errmsg(char **command, char **global_argv)
{
	char err_out[300] = "";

	if (!isatty(STDIN_FILENO))
	{
		strcpy(err_out, global_argv[0]);
		strcat(err_out, ": 1: ");
		strcat(err_out, command[0]);
		strcat(err_out, ": not found");
		write(STDERR_FILENO, err_out, strlen(err_out));
		write(STDERR_FILENO, "\n", 1);
	}
	else
	{
		strcpy(err_out, command[0]);
		strcat(err_out, ": command not found");
		write(STDOUT_FILENO, err_out, strlen(err_out));
		write(STDOUT_FILENO, "\n", 1);
	}
}
/**
 * end - ends the shell
 * @input: user input
 */
void end(char *input)
{
	if (input != NULL)
		free(input);
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	exit(0);
}

/**
 * err - ends the shell
 * @input: user input
 */
int errr(char *input)
{
	if (input != NULL)
		free(input);
	return (127);
}
