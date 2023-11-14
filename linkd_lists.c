#include "shell.h"

/**
 * adnode - function to add a node aat the start of list
 * @h: an address of the head node pointer
 * @s: the node field string
 * @digi: the node index
 * Return: the index of the node used by history
*/
list_t *adnode(list_t **h, const char *s, int digi)
{
	list_t *new_h;

	if (h == NULL)
	{
		return (NULL);
	}
	new_h = malloc(sizeof(list_t));
	if (new_h == NULL)
	{
		return (NULL);
	}
	set_mem((void *)new_h, 0, sizeof(list_t));
	new_h->dig = digi;
	if (s)
	{
		new_h->str = _sstrdup(s);
		if (new_h->str == NULL)
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
 * adnode_atend - function to add a node at the end of list
 * @h: a pointer to the address of the head node
 * @s: the node's field string
 * @digi: the node index
 * Return: the list size
*/
list_t *adnode_atend(list_t **h, const char *s, int digi)
{
	list_t *new_nd, *nd;

	if (h == NULL)
	{
		return (NULL);
	}

	nd = *h;
	new_nd = malloc(sizeof(list_t));
	if (new_nd == NULL)
	{
		return (NULL);
	}
	set_mem((void *)new_nd, 0, sizeof(list_t));
	new_nd->dig = digi;
	if (s)
	{
		new_nd->str = _sstrdup(s);
		if (new_nd->str == NULL)
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
	{
		*h = new_nd;
	}
	return (new_nd);
}

/**
 * listprnt_str - function that prints str element of a list_t linked list
 * @h: a pointer to the first node
 * Return: the size of the list
 */
size_t listprnt_str(const list_t *h)
{
	size_t j;

	j = 0;
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
 * delnode_atindx - function to delete node at specified index
 * @h: the pointer address to fist node
 * @inx: the index of the node to be deleted
 * Return: 0 always
*/
int delnode_atindx(list_t **h, unsigned int inx)
{
	unsigned int j;
	list_t *nd, *p_nd;

	j = 0;
	if (!*h || !h)
	{
		return (0);
	}
		if (!inx)
		{
			nd = *h;
			*h = (*h)->nxt;
			free(nd->str);
			free(nd);
			return (1);
	}
	nd = *h;
	while (nd)
	{
		if (j == inx)
		{
			p_nd->nxt = nd->nxt;
			free(nd->str);
			free(nd);
			return (1);
		}
		j++;
		p_nd = nd;
		nd = nd->nxt;
	}
	return (0);
}

/**
 * freelnkd_list - function to free all the nodes of a list
 * @h_p: the pointer address to the head node
 * Return: nothing
*/
void freelnkd_list(list_t **h_p)
{
	list_t *nd, *nx_nd, *h;

	if (!h_p || !*h_p)
	{
		return;
	}
	h = *h_p;
	nd = h;
	while (nd)
	{
		nx_nd = nd->nxt;
		free(nd->str);
		free(nd);
		nd = nx_nd;
	}
	*h_p = NULL;
}
