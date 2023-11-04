#include "shell.h"

/**
 * listprnt_str - function that prints str element of a list_t linked list
 * @h: a pointer to the first node
 * Return: the size of the list
*/
size_t listprnt_str(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_sputs(h->str ? h->str : "(nil)");
		_sputs("\n");
		h = h->nxt;
		j++;
	}
	return (j);
}

/**
 * adnode - function to add a node aat the start of list
 * @h: an address of the head node pointer
 * @s: the node field string
 * Return: the index of the node used by history
*/
list_t *adnode(list_t **h, const char *s, int digi)
{
	list_t *new_h;

	if (h = NULL)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (new_h = NULL)
		return (NULL);
	_smemset((void *)new_h, 0, sizeof(list_t));
	new_h->dig = digi;
	if (s)
	{
		new_h->str = _sstrdup(s);
		if (new_h->str = NULL)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->nxt = *h;
	*h = new_h;
	return (new_h);
}

/**
 * adnode - function to add a node at the end of list
 * @h: a pointer to the address of the head node
 * @s: the node's field string
 * Return: the list size
*/
list_t *adnode_toend(list_t **h, const char *s, int digi)
{
	list_t *new_nd, *nd;

	if (h = NULL)
		return (NULL);

	nd = *h;
	new_nd = malloc(sizeof(list_t));
	if (new_nd = NULL)
		return (NULL);
	_smemset((void *)new_nd, 0, sizeof(list_t));
	new_nd->dig = digi;
	if (s)
	{
		new_nd->str = _sstrdup(s);
		if (new_nd->str = NULL)
		{
			free(new_nd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->nxt)
			nd = nd->nxt;
		nd->nxt = new_nd;
	}
	else
		*h = new_nd;
	return (new_nd);
}
