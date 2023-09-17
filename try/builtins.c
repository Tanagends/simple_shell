#include "zimbo.h"
/**
 * zimbo_builtins - checks and execute builtins.
 * @toks: tokenized string.
 * Return: 1 (success).
 */
int zimbo_builtins(char **toks)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		if (strcmp(builtstr[i], toks[0]) == 0)
			return ((*builtfunc[i])(toks));
	}
	return (-1);
}
/**
 * exit - exits the shell.
 * @toks: tokenized input.
 * Return: 0 (Success)
 */
int zimbo_exit(char **toks)
{
	(void) toks;
	return (0);
}
/**
 * zimbo_env - prints environment variables.
 * @toks: tokenized input.
 * Return: 1 (Success).
 */
int zimbo_env(char **toks)
{
	int i = 0;

	if (toks[1] != NULL)
		return (1);
	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (1);
}
/**
 * zimbo_setenv - sets environment variables.
 * @toks: tokenized input.
 * Return: Always 1 (Success).
 */
int zimbo_setenv(char **toks)
{
	int i = 0;
	char new_env[MAX_LINE], *new_envp;

	if (toks[4] != NULL)
	{
		perror("Too many arguments");
		return (1);
	}
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i++], toks[1], strlen(toks[1])) == 0)
		{
			if (toks[3] == 0)
				return (1);
			zimbo_unset_env(toks);
			break;
		}
	}
	strcpy(new_env, toks[1]);
	strcat(new_env, "=");
	strcat(new_env, toks[2]);
	new_envp = malloc(strlen(new_env) + 1);
	if (new_envp == NULL)
	{
		perror("malloc");
		return (1);
	}
	strcpy(new_envp, new_env);
	environ[i] = new_envp;
	environ[i + 1] = NULL;
	return (1);
}
/**
 * zimbo_unset_env - unsets an environment variable.
 * @toks: tokenized input.
 * Return: integer.
 */
/*We might need to alter the return values*/
int zimbo_unset_env(char **toks)
{
	int i = 0, k = 0;

	if (toks[1] == NULL)
	{
		perror("Command not found");
		return (1);
	}
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], toks[1], strlen(toks[1])) == 0)
			break;
		i++;
	}
	if (environ[i] == NULL)
	{
		perror("Variable not found");
		return (1);
	}
	while (environ[k] != NULL)
		k++;
	k--;
	environ[i] = environ[k];
	environ[k] = NULL;
	return (1);
}
