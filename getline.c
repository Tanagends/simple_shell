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
	size_t len;
	char buffer[MAX_LINE] = "";
	ssize_t readd, total_red = 0, i;
	char *tmp;

	if (lineptr == NULL || n == NULL)
		return (-1);
	while (1)
	{
		readd = read(fd, buffer + total_red, MAX_LINE - total_red);
		if ((readd == -1) || (readd == 0 && total_red == 0))
			return (-1);
		total_red += readd;
		if (readd == 0 || (_memchr(buffer, '\n', total_red) != NULL))
			break;
	}
	buffer[total_red] = '\0';
	len = _strlen(buffer);
	*lineptr = malloc(len + 1);
	_memcpy((*lineptr), buffer, len + 1);
	*n = len;
	return ((ssize_t)len);
}
/**
 * _memchr - finds a character in a str.
 * @buffer: the string.
 * @c: the character.
 * @n: buffer character count.
 */
void *_memchr(char *buffer, char c, ssize_t n)
{
	ssize_t i;

	if (!buffer)
		return (NULL);
	for(i = 0; i < n; i++)
	{
		if (buffer[i] == c)
			return (buffer + i);
	}
	return (NULL);
}
