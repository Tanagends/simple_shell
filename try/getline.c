#include "zimbo.h"
/**
 * _getline - gets line from a file.
 * @lineptr: the variable to store stream input.
 * @n: premalloced usage memory
 * @fd: input source.
 * Return: at least actual character count input
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	size_t i = 0, len;
	char buffer[MAX_LINE] = "", char c[1];
	ssize_t readd;

	if (lineptr == NULL || n == NULL)
		return (-1);
	while (1)
	{
		readd = read(fd, c, 1);
		if (readd == -1)
			return (-1);
		if (readd == EOF)
		{
			if (i == 0)
				return (-1);
			break;
		}
		buffer[i++] = c[0];
		if (c[0] == '\n')
			break;
	}
	buffer[i] = '\0';
	len = strlen(buffer);
	realloc(*lineptr, len + 1);
	if (*lineptr == NULL)
		return (-1);
	strcpy((*lineptr), buffer);
	*n = len;
	return ((ssize_t)len);
}
