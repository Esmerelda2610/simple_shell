#include "shell.h"

/**
 * _sstrdup - function that duplicates a string
 * @s: the string to be duplicated
 * Return: a pointer to the string dulicated
*/

char *_sstrdup(const char *s)
{
	char *dup;
	int lng = 0;

	if (s == NULL)
		return (NULL);
	while (*s++)
		lng++;
	dup = malloc(sizeof(char) * (lng + 1));

	if (!dup)
		return (NULL);

	for (lng++; lng--;)
		dup[lng] = *--s;
	return (dup);

	return (dup);
}

/**
 * _sputs - function that prints an input string
 * @str: string that is to be printed
 * Return: 0
*/

void _sputs(char *str)
{
	while (*str)
	{
		_sputchar(*str);
		str++;
	}
}

/**
 * _sputchar - function that writes the c character to stdout
 * @c: the character to be printed
 * Return: 1 on success, -1 on error and set appropriately
*/

int _sputchar(char c)
{
	static int j;
	static char buff[WRT_BUFF_SIZE];

	if (c == BUFF_FLUSH || j >= WRT_BUFF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
	if (c != BUFF_FLUSH)
		buff[j++] = c;
	return (1);
}

/**
 * _sstrncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: number of bytes used
 * Return: the strings that have been concatenated
*/
char *_sstrncat(char *dest, char *src, int n)
{
	char *original_dest = dest;

	while (*dest)
	{
		dest++;
	}
	while (n-- > 0 && *src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';

	return (original_dest);
}

/**
 * _sstrncpy - function that copies a string
 * @dest: the destination string copied to
 * @src: the string source
 * @n: the number of characters copied
 * Return: the concatenated string
*/
char *_sstrncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}
