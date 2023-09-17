#include "zimbo.h"
/**
 * zimbo_cd - changes directory.
 * @toks: tokenized input.
 * Return: 1 (Success)
 */
int zimbo_cd(char **toks)
{
	int i;
	char pwd[MAX_LINE], nwd[MAX_LINE];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("getcwd error");
		return (1);
	}
	if (toks[1] == NULL)
		i = cd_home();
	else if (toks[2] != NULL)
	{
		perror("Too many arguments");
		return (1);
	}
	else if (strcmp(toks[1], "-") == 0)
		i = handle_cd();
	else
		i = chdir(toks[1]);
	if (i == 0)
	{
		if (getcwd(nwd, sizeof(nwd)) != NULL)
			set_old_new_pwd(pwd, nwd);
	}
	else
		perror(toks[1]);
	return (1);
}
/**
 * cd_home - handles home
 * Return: i (success).
 */
int cd_home()
{
	int i, k = 0;
	char *homeDir;

	while (environ[k] != NULL)
	{
		if (strncmp(environ[k], "HOME=", 5) == 0)
		{
			homeDir = environ[k] + 5;
			i = chdir(homeDir);
			return (i);
		}
		k++;
	}
	return (1);
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
	strcpy(old, "setenv OLDPWD ");
	strcat(old, pwd);
	strcat(old, "1");
	strcpy(new, "setenv PWD ");
	strcat(new, nwd);
	strcat(new, "1");
	oldp = malloc(strlen(old) + 1);
	newp = malloc(strlen(new) + 1);
	if (newp == NULL || oldp == NULL)
	{
		perror("Malloc error");
		return;
	}
	strcpy(oldp, old);
	strcpy(newp, new);
	zimbo_setenv(zimbo_split(oldp));
	zimbo_setenv(zimbo_split(newp));
	free(oldp);
	free(newp);
}
/**
 * handle_cd - executes cd -.
 * Return: 1 (Success)
 */
int handle_cd()
{
	char *old_wd = NULL, *cwd = NULL;
	int k = 0, i;

	while (environ[k] != NULL)
	{
		if (strncmp(environ[k], "OLDPWD=", 7) == 0)
		{
			old_wd = environ[k] + 7;
			if (getcwd(cwd, sizeof(cwd)) == NULL)
				return (1);
			i = chdir(old_wd);
			break;
		}
		k++;
	}
	if (environ[k] == NULL)
	{
		perror("Old directory not found");
		return (1);
	}
	return (i);
}
