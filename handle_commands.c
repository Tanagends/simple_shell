#include "zimbo.h"
/**
 * handle_commands - handles commands.
 * @input: input command
 * @argv: an array of strings
 * Return: 1 (Special Case)
 */
int handle_commands(char *input, char *argv[])
{
	char *ptr, **toks;

	ptr = input;
	if (_memchr(ptr, ';', _strlen(ptr)) != NULL)
	{
		while (_memchr(ptr, ';', _strlen(ptr)))
		{
			ptr = _memchr(ptr, ';', _strlen(ptr));
			*ptr = '\0';
			ptr++;
			if (*ptr == '\0')
			{
				ptr++;
				continue;
			}
			toks = zimbo_split(input);
			if (toks == NULL)
				return (-1);
			zimbo_execute(toks, argv);
			free(toks);
			input = ptr;
		}
		ptr = input;
		toks = zimbo_split(input);
		if (toks == NULL)
		{
			return (-1);
			free(toks);
		}
		zimbo_execute(toks, argv);
		free(toks);
		return (1);
	}
	return (0);
}

/**
* handle_comments - function to search and handle comments
* @input: The character to search for
* Return: Return nothing
*/

void handle_comments(char *input)
{
	char *ptr;

	if (input == NULL)
	{
		return;
	}
	ptr = input;
	while ((ptr = _memchr(ptr, '#', _strlen(ptr))) != NULL)
	{
		if (*ptr == '#')
			*ptr = '\0';
		ptr++;
	}
}
