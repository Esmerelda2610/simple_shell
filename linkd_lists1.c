#include "shell.h"

/**
 * getnode_indx - function to get the node index
 * @h: a pointer to the head of the list
 * @nd: a ppointer to the node
 * Return: the index of node, otherwise -1
*/
ssize_t getnode_indx(list_t *h, list_t *nd)
{
	size_t k;

	k = 0;

	while (h != NULL)
	{
		if (h == nd)
			return (k);
		h = h->nxt;
		k++;
	}
	return (-1);
}

/**
 * initial_node - function to return node with string starting with prefix
 * @nd: a pointer to the head of the list
 * @prx: the matching string
 * @t: character following prefix to match
 * Return: NULL or matching node
*/
list_t *initial_node(list_t *nd, char *prx, char t)
{
	char *d;

	d = NULL;

	while (nd != NULL)
	{
		d = pre_substr(nd->str, prx);
		if (d && ((t == -1) || (*d == t)))
			return (nd);
		nd = nd->nxt;
	}
	return (NULL);
}

/**
 * list_prnt - function to print all elements of a list
 * @head: a pointer to the first node
 * Return: the list size
*/
size_t list_prnt(const list_t *head)
{
	size_t m;

	m = 0;

	while (head != NULL)
	{
		_sputs(digit_convrt(head->dig, 10, 0));
		_sputchar(':');
		_sputchar(' ');
		_sputs(head->str ? head->str : "(nil)");
		_sputs("\n");
		head = head->nxt;
		m++;
	}
	return (1);
}

/**
 * convlist_2str - function to return a string array of list->str
 * @hd: a pointer to the first node
 * Return: a string array
*/
char **convlist_2str(list_t *hd)
{
	char *s;
	char **sts;
	list_t *nde = hd;
	size_t m = lenof_list(hd), k;

	if (!hd || !m)
		return (NULL);
	sts = malloc(sizeof(char *) * (m + 1));
	if (sts == NULL)
		return (NULL);
	for (m = 0; nde; nde = nde->nxt, m++)
	{
		s = malloc(_sstrlen(nde->str) + 1);
		if (s == NULL)
		{
			for (k = 0; k < m; k++)
				free(sts[k]);
			free(sts);
			return (NULL);
		}
		s = _sstrcpy(s, nde->str);
		sts[m] = s;
	}
	sts[m] = NULL;
	return (sts);
}

/**
 * lenof_list - measures the linked list length
 * @head: a pointer to the first node
 * Return: the list size
*/
size_t lenof_list(const list_t *head)
{
	size_t k;

	k = 0;

	while (head != NULL)
	{
		head = head->nxt;
		k++;
	}
	return (k);
}
