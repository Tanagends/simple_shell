#include "zimbo.h"
/**
 * err_home - displays home error
 */
void err_home(void)
{
	char buffer[300] = "";

	_strcpy(buffer, global_argv[0]);
	_strcat(buffer, ": cd: HOME not set");
	write(STDOUT_FILENO, buffer, strlen(buffer));
	write(STDOUT_FILENO, '\n', 1);
}

/**
 * errmsg - displays error message.
 * @command: command entered.
 */
void errmsg(char **command, char **global_argv)
{
	char err_out [300] = "";

	if (!isatty(STDIN_FILENO))
	{
		strcpy(err_out, global_argv[0]);
		strcat(err_out, ": 1: ");
		strcat(err_out, command[0]);
		strcat(err_out, ": not found");
		write(STDOUT_FILENO, err_out, strlen(err_out));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		strcpy(err_out, command[0]);
		strcat(err_out, ": command not found");
		write(STDOUT_FILENO, err_out, strlen(err_out));
		write(STDOUT_FILENO, "\n", 1);
	}
	return;
}
