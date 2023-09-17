#include "zimbo.h"
/**
 * _strtok - tokenizes the string.
 * @string: the string to be tokenized.
 * @delimiters: the delimiter.
 * Return: tokenized.
 */
char *_strtok(char *string, const char *delimiters)
{
	static char *remaining;
	char *delimptr, *token;

	if (string != NULL)
		remaining = string;
	if (remaining == NULL || *remaining == '\0')
		return (NULL);
	delimptr = strpbrk(remaining, delimiters);
	if (delimptr != NULL)
	{
		*delimptr = '\0';
		delimptr++;
		while (delim(delimptr, delimiters))
		{
			*delimptr = '\0';
			delimptr++;
		}
	}
	token = remaining;
	remaining = delimptr;
	if (*token == '\0')
		return (NULL);
	return (token);
}
/**
 * delim - looks if next character is in delim.
 * @token: remaining string
 * @lim: delimiters.
 * Return: 1 (Success)
 */
int delim(char *token, const char *lim)
{
	int k = 0;
	char c;

	if (token == NULL || lim == NULL)
		return (0);
	c = *token;
	for (k = 0; lim[k] != '\0'; k++)
	{
		if (c == lim[k])
			return (1);
	}
	return (0);
}
