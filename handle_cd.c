#include "zimbo.h"

/**
 * zimbo_exit - exits the shell.
 * @toks: tokens
 * Return: 0 (Success)
 */
int zimbo_exit(char **toks)
{
	int exit_status;

	if (toks[1] != NULL)
	{
		exit_status = atoi(toks[1]);
		if (exit_status != 0)
			exit(exit_status);
		else if (exit_status == 0 && toks[1] == "0")
			exit(0);
		else
			exit(0);
	}		
	return (0);
}
/**
 * zimbo_cd - changes directory.
 * @toks: tokenized input.
 * Return: 1 (Success)
 */
int zimbo_cd(char **toks)
{
	int i;
	char *pwd, *nwd;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("getcwd error");
		return (1);
	}
	if (toks[1] == NULL)
	{
		i = cd_home();
		if (!i)
			err_home();
	}
	else if (toks[2] != NULL)
		i = 3;
	else if (_strcmp(toks[1], "-") == 0)
		i = handle_cd(toks);
	else
		i = chdir(toks[1]);
	if (i == 0)
	{
		if (getcwd(nwd, sizeof(nwd)) != NULL)
		{
			set_old_new_pwd(pwd, nwd);
			free(nwd);
		}
	}
	else
		err_cd(toks);
	free(pwd);
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
	char old[MAX_LINE], new[MAX_LINE], *oldp, *newp;

	memset(old, 0, sizeof(old));
	memset(new, 0, sizeof(new));
	_strcpy(old, "setenv OLDPWD ");
	_strcat(old, pwd);
	_strcat(old, "1");
	_strcpy(new, "setenv PWD ");
	_strcat(new, nwd);
	_strcat(new, "1");
	oldp = malloc(strlen(old) + 1);
	newp = malloc(strlen(new) + 1);
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
 * handle_cd - handles cd.
 * @toks: tokenized input.
 * Return: 1 (Success)
 */
int handle_cd(char **toks)
{
	char *old_wd = NULL, *cwd = NULL;
	int k = 0, i;

	(void) toks;
	while (environ[k] != NULL)
	{
		if (_strncmp(environ[k], "OLDPWD=", 7) == 0)
		{
			old_wd = environ[k] + 7;
			i = chdir(old_wd);
			return (i);
		}
		k++;
	}
	if (environ[k] == NULL)
	{
		/*perror("Old directory not found");*/
		return (4);
	}
	/*return (i);*/
}
