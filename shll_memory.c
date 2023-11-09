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
 * free_str - function to free a main string
 * @strs: the main string
 */
void free_str(char **strs)
{
	char **j = strs;

	if (!strs)
		return;
	while (*strs)
		free(*strs++);
	free(j);
}

/**
 * shll_realloc - function to reallocate memory block
 * @p: a pointer to older malloc'ed memory block
 * @old: the byte size of of previous block
 * @new: the byte size of the new memory block
 * Return: a pointer to the previous memory block
*/
void *shll_realloc(void *p, unsigned int old, unsigned int new)
{
	char *pns;

	if (!p)
		return (malloc(new));
	if (!new)
		return (free(p), NULL);
	if (new == old)
		return (p);

	pns = malloc(new);
	if (!pns)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		pns[old] = ((char *)p)[old];
	free(p);
	return (pns);
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
	return (0);
}

