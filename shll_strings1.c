#include "shell.h"

/**
 * _sstrdup - function that duplicates a string
 * @s: the string to be duplicated
 * Return: a pointer to the string dulicated
*/

char *_sstrdup(const char *s)
{
	char *dup;
	int lgth = 0;

	if (s == NULL)
		return (NULL);
	while (*s++)
		lgth++;
	dup = malloc(sizeof(char) * (lgth + 1));

	if (!dup)
		return (NULL);

	for (lgth++; lgth--;)
		dup[lgth] = *--s;
	return (dup);
}

/**
 * _sputs - function that prints an input string
 * @s: string that is to be printed
 * Return: 0
*/

void _sputs(char *s)
{
	int k = 0;

	if (!s)
		return;
	while (s[k] != '\0')
	{
		_sputchar(s[k]);
		k++;
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
 * _sstrncpy - function that copies a string
 * @des: the destination string copied to
 * @src: the string source
 * @n: the number of characters copied
 * Return: the concatenated string
*/
char *_sstrncpy(char *des, char *src, int n)
{
	int k, m;
	char *d = des;

	k = 0;
	while (src[k] != '\0' && k < n - 1)
	{
		des[k] = src[k];
		k++;
	}
	if (k < n)
	{
		m = k;
		while (m < n)
		{
			des[m] = '\0';
			m++;
		}
	}
	return (d);
}

/**
 * _sstrncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: number of bytes used
 * Return: the strings that have been concatenated
 */
char *_sstrncat(char *dst, char *sce, int n)
{
	int k = 0, m = 0;
	char *original_dest = dst;

	while (dst[k] != '\0')
	{
		k++;
	}
	while (sce[m] != '\0' && m < n)
	{
		dst[k] = sce[m];
		k++;
		m++;
	}
	if (m < n)
		dst[k] = '\0';
	return (original_dest);
}
