#include "zimbo.h"
/**
 * _strlen - computes string length
 * @str: the string
 * Return: the string length
 */
size_t _strlen(const char *str)
{
	size_t i;

	if (str == NULL)
		return (0);
	for (i = 0; str[i] != '\0'; i++)
		;
	return (i);
}
/**
 * _strcpy - copies string into a buffer.
 * @dest: destination buffer.
 * @src: source buffer.
 * Return: dest with copied contents.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	if (src == NULL || dest == NULL)
		return (NULL);
	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
/**
 * _strcat - concatenates two strings
 * @dest: forestring.
 * @src: terminal string.
 * Return: concatenated string.
 */
char *_strcat(char *dest, const char *src)
{
	size_t i = 0, k = 0;

	if (dest == NULL)
		return (src);
	if (src == NULL)
		return (dest);
	for (i = 0; dest[i] != '\0'; i++)
		;
	for (k = 0; src[k] != '\0'; k++)
		dest[i++] = src[k];
	dest[i] = '\0';
	return (dest);
}
/**
 * _strncmp - compares two strings
 * @str1: first string.
 * @str2: second string.
 * @n: character comparison count.
 * Return: 0 (if equal).
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	if (str1 == NULL && str2 == NULL)
		return (0);
	if (str1 == NULL)
		return (-1);
	if (str2 == NULL)
		return (1);
	for (i = 0; i < n; i++)
	{
		if (str1[i] == '\0' || str2[i] == '\0')
			break;
		if (str1[i] > str2[i])
			return (1);
		if (str1[i] < str2[i])
			return (-1);
	}
	return (0);
}
/**
 * _strcmp - compares two strings
 * @str1: first string.
 * @str2: second string.
 * Return: 0 (if equal).
 */
int _strcmp(const char *str1, const char *str2)
{
	size_t i;

	if (str1 == NULL && str2 == NULL)
		return (0);
	if (str1 == NULL)
		return (-1);
	if (str2 == NULL)
		return (1);
	for (i = 0; str1[i] == '\0' && str2[i] == '\0'; i++)
	{
		if (str1[i] == '\0' && str2[i] != '\0')
			return (-1);
		if (str1[i] != '\0' && str2[i] == '\0')
			return (1);
		if (str1[i] > str2[i])
			return (1);
		if (str1[i] < str2[i])
			return (-1);
	}
	return (0);
}
