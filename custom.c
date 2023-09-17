#include "zimbo.h"
/**
 * _memcpy - copies memory
 * @dest: destination block.
 * @src: source block.
 * @n: number of bytes.
 */
void *memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	char *charDest = (char *)dest;
	const char *charSrc = (const char *)src;

	for (i = 0; i < n; i++)
		charDest[i] = charSrc[i];
	return (charDest);
}
