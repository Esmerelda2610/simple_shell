#include "shell.h"

/**
 * set_mem - function to fill memory with constant byte
 * @p: a pointer to memory zone
 * @t: the byte that is filled with p
 * @m: the amount of bytes used to fill memory zone
 * Return: a pointer p to the memory zone
*/
char *set_mem(char *p, char t, unsigned int m)
{
	unsigned int j;

	for (j = 0; j < m; j++)
		p[j] = t;
	return (p);
}

/**
 * shll_realloc - function to reallocate memory block
 * @p: a pointer to older malloc'ed memory block
 * @old: the byte size of of previous block
 * @new: the byte size of the new memory block
*/
void shll_realloc(void *p, unsigned int old, unsigned int new)
{
	char *pns;

	if (p == NULL)
		return (malloc(new));
	if (new == NULL)
		return (free(p), NULL);
	if (new == old)
		return (p);

	pns = malloc(new);
	if (pns == NULL)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		pns[old] = ((char *)p)[old];
	free(p);
	return (pns);
}

/**
 * free_str - function to free a main string
 * @strs: the main string
*/
void free_str(char **strs)
{
	char **j = strs;

	if (strs == NULL)
		return;
	while (strs != NULL)
		free(*strs);
	free(j);
}

/**
 * free_ptr - function to free a pointer and NULL the address
 * @p: the address of the free'd pointer
 * Return: if successful 1, 0 otherwise
*/
int free_ptr(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
}

/**
 * atoi_errs - function to convert integer fromstring
 * @str: the converted string
 * Return: if no numbers in string 0, on fail -1
*/
int atoi_errs(char *str)
{
	unsigned long int res;
	int j;
	res = 0;
	j = 0;

	if (*str == '+')
		str++;
	for (j = 0; str[j] != '\0'; j++)
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			res *= 10;
			res += (str[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}
