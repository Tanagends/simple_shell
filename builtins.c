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
		write(1, environ[i], _strlen(environ[i]));
		write(1, "\n", 1);
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
	/*int i = 0;
	char new_env[MAX_LINE], *new_envp;*/

	if (toks[1] == NULL)
	{
		zimbo_env(toks);
		return (1);
	}
	/*while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], toks[1], _strlen(toks[1])) == 0)
		{
			free(environ[i]);
			_strcpy(environ[i], toks[1]);
			_strcat(environ[i], "=");
			_strcat(environ[i], toks[2]);
			return (1);
		}
	i++;
	}
	_strcpy(new_env, toks[1]);
	_strcat(new_env, "=");
	if (toks[2] != NULL)
		_strcat(new_env, toks[2]);
	new_envp = malloc(_strlen(new_env) + 1);
	if (new_envp == NULL)
	{
		write(STDERR_FILENO, "Couldn't set", 12);
		return (1);
	}
	_strcpy(new_envp, new_env);
	environ[i] = new_envp;
	environ[i + 1] = NULL;*/
	setenv(toks[1], toks[2], 1);
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
		if (_strncmp(*env, toks[1], _strlen(toks[1])) == 0 &&
				*env[_strlen(toks[1])] == '=')
		{
			*env = update;
			return (1);
		}
	}
	return (0);
}
/**
 * zimbo_unset_env - unsets an environment variable.
 * @toks: tokenized input.
 * Return: update_env.
 */
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
		if (_strncmp(environ[i], toks[1], _strlen(toks[1])) == 0)
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
/**
 * zimbo_builtins - checks and execute builtins.
 * @toks: tokenized string.
 * Return: 1
 */
int zimbo_builtins(char **toks)
{
	int i;
	char *builtstr[] = {"setenv", "env", "exit", "unsetenv"};
	typedef int (*Builtfunc)(char **);
	Builtfunc builtfunc[5] = {zimbo_setenv,
				zimbo_env,
				zimbo_exit,
				zimbo_unset_env};

	for (i = 0; i < 4; i++)
	{
		if (_strcmp(builtstr[i], toks[0]) == 0)
			return ((*builtfunc[i])(toks));
	}
	return (-1);
}
