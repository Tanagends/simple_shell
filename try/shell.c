#include "zimbo.h"
/**
 * main - a simple shell
 * Return: 0(Always success).
 */
/* command prompt duplicating upon null input*/
/* double free error*/
/* error messages*/
/* executing a command only on the first prompt*/
char **environ;
char *builtstr[] = {"cd", "setenv", "env", "exit", "unsetenv"};
int (*builtfunc[])(char **toks) = {zimbo_cd, zimbo_setenv,
	zimbo_env, zimbo_exit, zimbo_unset_env};
int main(void)
{
	char *input, **toks;
	size_t size = 0;
	ssize_t i, k;
	int status = 1;

	while (status)
	{
		i = write(STDOUT_FILENO, "Zimboshell$ ", 12);
		if (i != -1)
		{
			k = getline(&input, &size, stdin);
			if (k == -1)
			{
				write(STDOUT_FILENO, "\n", 1);
				break;
			}
			toks = zimbo_split(input);
			status = zimbo_execute(toks);
		/*	free(input);*/
			free(toks);
		}
	}
	return (0);
}
/**
 * zimbo_split - tokenize string.
 * @string: string to be tokenized.
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
 * @toks: tokenized input.
 * Return: 1 (Success)
 */
int zimbo_execute(char **toks)
{
	pid_t _pid;
	int status;
	char *path_handler = NULL;
	int builtins = -1;

	if (toks[0] == NULL)
		return (1);
	builtins = zimbo_builtins(toks);
	if (builtins != -1)
		return (builtins);
	path_handler = zimbo_path__handler(toks);
	if (path_handler != NULL || access(toks[0], X_OK) == 0)
	{
		_pid = fork();
		if (_pid == 0)
		{
			if (path_handler != NULL)
			{
				if (execve(path_handler, toks, environ) == -1)
				{
					perror(toks[0]);
					exit(errno);
				}
			}
			else
			{
				if (execve(toks[0], toks, environ) == -1)
				{
					perror(toks[0]);
					exit(errno);
				}
			}
		}
		else if (_pid > 0)
			waitpid(_pid, &status, WUNTRACED);
		else
			perror("fork error"); /*If fork fails*/
	}
	else
		perror("Error");
	return (1);
}
/**
 * zimbo_path__handler - handles the path
 * @toks: tokenized input.
 * Return: Found path.
 */
char *zimbo_path__handler(char **toks)
{
	char *path;
	char *path_token, *ammended_path;
	char full_path[300];
	int i;
	/*PATH= /bin:/bin/local:/usr/bin      example*/

	/* Iterate over the 'environ' array to find the 'PATH' variable*/
	for (i = 0; environ[i] != NULL; i++)
	{
		/* Check if the current environment variable starts with "PATH="*/
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;  /* Extract the value by skipping "PATH="*/
			break;
		}
	}
	if (environ[i] != NULL)
	{
		path_token = strtok(path, ":");
		while (path_token != NULL)
		{
			strcpy(full_path, path_token);  /* Copy 'path' to 'full_path'*/
			strcat(full_path, "/");/* Append a forward slash*/
			strcat(full_path, toks[0]); /* Append 'command'*/
			if (access(full_path, X_OK) == 0)
			{
				ammended_path = strdup(full_path);
				return (ammended_path);
			}
			path_token = strtok(NULL, ":");
		}
	}
	return (NULL);
}
