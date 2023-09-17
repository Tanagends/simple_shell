#include "zimbo.h"
/**
 * _memcpy - copies memory
 * @dest: destination block.
 * @src: source block.
 * @n: number of bytes.
 * Return: void.
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	char *charDest = (char *)dest;
	const char *charSrc = (const char *)src;

	for (i = 0; i < n; i++)
		charDest[i] = charSrc[i];
	return (charDest);
}
/**
 * _strdup - duplicates string
 * @str: the string.
 * Return: the string.
 */
char *_strdup(char *str)
{
	char *dup;

	if (str == NULL)
	{
		printf("string passed is NULL\n");
		return (NULL);
	}
	dup = malloc(_strlen(str) + 1);
	if (!dup)
	{
		perror("strdup malloc error");
		return (NULL);
	}
	_strcpy(dup, str);
	return (dup);
}
