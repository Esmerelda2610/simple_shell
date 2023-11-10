#include "shell.h"

/**
 * _sstrchr - finds a character in a string
 * @s: the string searched
 * @c: the character searched for
 * Return: NULL
 */
char *_sstrchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');
	return (NULL);
}

/**
 * split_str - function that splits words from strings
 * ignoring repeat delimitors
 * @spt: the string to be split
 * @dstr: a delimitor string
 * Return: pointer to string array, NULL on fail
 */
char **split_str(char *spt, char *dstr)
{
	int a, b, c, d, numcnt = 0;
	char **p;

	if (spt == NULL || spt[0] == 0)
		return (NULL);
	if (!dstr)
		dstr = " ";
	for (a = 0; spt[a] != '\0'; a++)
		if (!is_delim(spt[a], dstr) && (is_delim(spt[a + 1], dstr) || !spt[a + 1]))
			numcnt++;

	if (numcnt == 0)
		return (NULL);
	p = malloc((1 + numcnt) * sizeof(char *));
	if (!p)
		return (NULL);
	for (a = 0, b = 0; b < numcnt; b++)
	{
		while (is_delim(spt[a], dstr))
			a++;
		c = 0;
		while (!is_delim(spt[a + c], dstr) && spt[a + c])
			c++;
		p[b] = malloc((c + 1) * sizeof(char));
		if (!p[b])
		{
			for (c = 0; c < b; c++)
				free(p[c]);
			free(p);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			p[b][d] = spt[a++];
		p[b][d] = 0;
	}
	p[b] = NULL;
	return (p);
}

/**
 * split_delimstr - function that splits words from strings
 * @spt: the string to be split
 * @dstr: a delimitor string
 * Return: pointer to string array, NULL on fail
 */
char **split_delimstr(char *spt, char dstr)
{
	int a, b, c, d, numcnt = 0;
	char **p;

	if (spt == NULL || spt[0] == 0)
		return (NULL);
	for (a = 0; spt[a] != '\0'; a++)
		if ((spt[a] != dstr && spt[a + 1] == dstr) ||
		 (spt[a] != dstr && !spt[a + 1]) || spt[a + 1] == dstr)
			numcnt++;

	if (numcnt == 0)
		return (NULL);
	p = malloc((1 + numcnt) * sizeof(char *));
	if (!p)
		return (NULL);
	for (a = 0, b = 0; b < numcnt; b++)
	{
		while (spt[a] == dstr && spt[a] != dstr)
			a++;
		c = 0;
		while (spt[a + c] != dstr && spt[a + c] && spt[a + c] != dstr)
			c++;
		p[b] = malloc((c + 1) * sizeof(char));
		if (!p[b])
		{
			for (c = 0; c < b; c++)
				free(p[c]);
			free(p);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			p[b][d] = spt[a++];
		p[b][d] = 0;
	}
	p[b] = NULL;
	return (p);
}
