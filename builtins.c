#include "zimbo.h"

/**
 * zimbo_env - prints environment variables.
 * @toks: tokenized input.
 * Return: 1 (Success).
 */
int zimbo_env(char **toks)
{
	int i = 0;

	if (toks[1] != NULL)
	{
		err_env(toks);
		return (1);
	}
	while (environ[i] != NULL)
	{
		write(1, environ[i], strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
	return (1);
}
/** zimbo_setenv - sets environment variables.
 * @toks: tokenized input.
 * Return: Always 1 (Success).
 */
int zimbo_setenv(char **toks)
{
	int i = 0;
	char new_env[MAX_LINE], *new_envp;

	if (toks[1] == NULL)
	{
		zimbo_env(toks);
		return (1);
	}
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], toks[1], strlen(toks[1])) == 0)
		{
			free(environ[i]);
			strcpy(environ[i], toks[1]);
			strcat(environ[i], "=");
			strcat(environ[i], toks[2]);
			return (1);
		}
	i++;
	}
	strcpy(new_env, toks[1]);
	strcat(new_env, "=");
	if (toks[2] != NULL)
		strcat(new_env, toks[2]);
	new_envp = malloc(strlen(new_env) + 1);
	if (new_envp == NULL)
	{
		write(STDERR_FILENO, "Couldn't set", 12);
		return (1);
	}
	strcpy(new_envp, new_env);
	environ[i] = new_envp;
	environ[i + 1] = NULL;
	return (1);
}
/**
 * exist_env - updates an existing env
 * @update: the new
 * @toks: tokenized command
 * Return: 1 (if it exists)
 */
int exist_env(char *update, char **toks)
{
	char **env;

	env = environ;
	while (*env != NULL)
	{
		if (strncmp(*env, toks[1], strlen(toks[1])) == 0 && 
				*env[strlen(toks[1])] == '=')
		{
			*env = update;
			return (1);
		}
	}
	return (0);
}
/**
 * store_env - frees environment.
 * @envp: pointer to an env.
 */
void store_env(char *envp)
{
	static char *new_envp_array[20] = {};
	static int i = 0;

	new_envp_array[i] = envp;
	i++;
	return;
}
/**
 * zimbo_unset_env - unsets an environment variable.
 * @toks: tokenized input.
 * Returupdate_env
*We might need to alter */
int zimbo_unset_env(char **toks)
{
	int i = 0, k = 0;

	if (toks[1] == NULL)
	{
		write(STDERR_FILENO, "Couldn't set", 12);
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
		write(STDERR_FILENO, "Couldn't set", 12);
		return (1);
	}
	while (environ[k] != NULL)
		k++;
	k--;
	environ[i] = environ[k];
	environ[k] = NULL;
	return (1);
}
