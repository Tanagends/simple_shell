#include "zimbo.h"

/**
 * zimbo_exit - exits the shell.
 * @toks: tokens
 * Return: 0 (Success)
 */
int zimbo_exit(char **toks)
{
	int exit_status;
	/*char err[300] = "./hsh: 1: exit: Illegal number: ";*/

	if (toks[1] != NULL)
	{
		exit_status = atoi(toks[1]);
		if (exit_status > 0 || exit_status < 0)
			exit(exit_status);
		else if (exit_status == 0 && _strcmp(toks[1], "0") == 0)
			return (0);
		else if (exit_status == 0 && _strcmp(toks[1], "0") != 0)
		{
		/*	_strcat(err, toks[1]);*/
		/*	_strcat(err, "\n");*/
		/*	write(STDERR_FILENO, err, _strlen(err));*/
		/*	exit(2);*/
			return (0);
		}
	}
	return (0);
}
/**
 * zimbo_cd - changes directory.
 * @toks: tokenized input.
 * @argv: shell commands.
 * Return: 1 (Success)
 */
int zimbo_cd(char **toks, char **argv)
{
	int i;
	char pwd[300] = "", nwd[300] = "";

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("getcwd error");
		return (1);
	}
	if (toks[1] == NULL)
		i = cd_home();
	else if (toks[2] != NULL)
		i = 3;
	else if (_strcmp(toks[1], "-") == 0)
		i = handle_cd(toks);
	else
		i = chdir(toks[1]);
	if (i == 0)
	{
		if (getcwd(nwd, sizeof(nwd)) != NULL)
			set_old_new_pwd(pwd, nwd);
	}
	else
		err_cd(toks, i, argv);
	return (1);
}
/**
 * cd_home - handles home
 * Return: i (success).
 */
int cd_home(void)
{
	int i, k = 0;
	char *homeDir;

	while (environ[k] != NULL)
	{
		if (_strncmp(environ[k], "HOME=", 5) == 0)
		{
			homeDir = environ[k] + 5;
			i = chdir(homeDir);
			return (i);
		}
		k++;
	}
	return (2);
}
/**
 * set_old_new_pwd - updates PWD and OLDPWD.
 * @pwd: OLDPWD value.
 * @nwd: PWD value.
 */
void set_old_new_pwd(char *pwd, char *nwd)
{
	char old[MAX_LINE] = "", new[MAX_LINE] = "";
	/*char *no[3] = {"setenv", "OLDPWD", pwd};*/
	/*char *np[3] = {"setenv", "PWD", nwd};*/
	/*char old[MAX_LINE] = "", new[MAX_LINE] = "";*/
	char *oldp, *newp;
	/*no[0] = "setenv";*/
	/*no[1] = "OLDPWD";*/
	/*no[2] = pwd;*/
	/*np[0] = "setenv";*/
	/*np[1] = "PWD";*/
	/*np[2] = nwd;*/

	_strcpy(old, "setenv OLDPWD ");
	_strcat(old, pwd);
	_strcat(old, "1");
	_strcpy(new, "setenv PWD ");
	_strcat(new, nwd);
	_strcat(new, "1");
	oldp = malloc(_strlen(old) + 1);
	newp = malloc(_strlen(new) + 1);
	if (newp == NULL || oldp == NULL)
	{
		perror("Malloc error");
		return;
	}
	_strcpy(oldp, old);
	_strcpy(newp, new);
	setenv("OLDPWD", pwd, 1);
	setenv("PWD", nwd, 1);
	free(oldp);
	free(newp);
}
/**
 * handle_cd - handles cd - command.
 * @toks: tokenized input.
 * Return: 1 (Success)
 */
int handle_cd(char __attribute__((unused)) **toks)
{
	char *old_wd = NULL;
	int k = 0, i;
	char cwd[300] = "", err[300] = "./hsh: 1: cd: can't cd to ";

	while (environ[k] != NULL)
	{
		if (_strncmp(environ[k], "OLDPWD=", 7) == 0)
		{
			old_wd = environ[k] + 7;
			i = chdir(old_wd);
			write(STDOUT_FILENO, old_wd, _strlen(old_wd));
			write(STDOUT_FILENO, "\n", 1);
			return (i);
		}
		k++;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		write(STDOUT_FILENO, "getcwd error", 12);
		return (4);
	}
	_strcat(err, cwd);
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "OLDPWD not set", 14);
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		write(STDOUT_FILENO, cwd, _strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (4);
}
