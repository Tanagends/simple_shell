#include "zimbo.h"
/**
 * handle_commands - handles commands.
 * @input: input command
 * Return: 1 (Special Case)
 */
int handle_commands(char *input)
{
	char *ptr, **toks, *p;
	int i = 0, k;

	if (_memchr(input, ';', _strlen(input)) == NULL &&
		_memchr(input, '&', _strlen(input)) == NULL &&
		_memchr(input, '|', _strlen(input)) == NULL &&
		_memchr(input, '#', _strlen(input)) == NULL)
		return (0);

	if (_memchr(input, ';', _strlen(input)) != NULL)
	{
		ptr = _memchr(input, ';', _strlen(input));
		while (ptr != NULL)
		{
			*ptr = '\0';
			ptr++;
			i++;
			ptr = _memchr(ptr, ';', _strlen(ptr));
		}
		p = input;
		for (k = 0; k < i + 1; k++)
		{
			toks = zimbo_split(p);
			zimbo_execute(toks, global_argv);
			p = _memchr(p, '\0', (_strlen(p) + 1));
			p++;
			free(toks);
		}
		return (1);
	}
	/*handle_and_or(input);*/
	return (1);
}
