#include "zimbo.h"
/**
 * err_home - displays home error
 */
void err_home(void)
{
	char buffer[300] = "";

	strcpy(buffer, global_argv[0]);
	strcat(buffer, ": cd: HOME not set");
	write(STDOUT_FILENO, buffer, strlen(buffer));
	write(STDOUT_FILENO, '\n', 1);
}
