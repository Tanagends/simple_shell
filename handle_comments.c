#include "zimbo.h"
/**
* handle_comments - function to search and handle comments
* @toks: The comment to be handled from input (toks)
*
* Return: Return nothing
*/

void handle_comments(char *toks)
{
	char *cmnt = _memchr(toks, '#', _strlen(toks));

	if (toks == NULL)
	{
	return;
	}
	while (cmnt != NULL)
	{
		*cmnt = '\0';
		cmnt = _memchr(cmnt + 1, '#');
	}
}
