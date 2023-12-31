#include "shell.h"

/**
 * rmv_alias - unsets the alias
 * @data: a struct of parameters
 * @s: the alias string
 * Return: rtrn
 */
int rmv_alias(data_t *data, char *s)
{
	char *b, d;
	int rtrn;

	b = _sstrchr(s, '=');
	if (!b)
	{
		return (1);
	}
	d = *b;
	*b = 0;
	rtrn = delnode_atindx(&(data->alias),
		getnode_indx(data->alias, initial_node(data->alias, s, -1)));
	*b = d;
	return (rtrn);
}

/**
 * aliaset - function to set an alias to a string
 * @data: the struct parameter
 * @s: the alias string
 * Return: 0 always, on error 1
 */
int aliaset(data_t *data, char *s)
{
	char *b;

	b = _sstrchr(s, '=');
	if (b == NULL)
	{
		return (1);
	}
	if (!++b)
	{
		return (rmv_alias(data, s));
	}
	rmv_alias(data, s);
	return (adnode_atend(&(data->alias), s, 0) == NULL);
}

/**
 * alias_prnt - function to print an alias string
 * @node: an alias node
 * Return: 0 on success, on error 1
*/
int alias_prnt(list_t *node)
{
	char *d = NULL, *e = NULL;

	if (node != NULL)
	{
		d = _sstrchr(node->str, '=');
		for (e = node->str; e <= d; e++)
		{
			_sputchar(*e);
		}
		_sputchar('\'');
		_sputs(d + 1);
		_sputs("'\n");
		return (0);
	}
	return (1);
}

/**
 * shll_alias - functions similar to the alias built-in
 * @data: a struct of potential arguments
 * Return: 0 always
 */
int shll_alias(data_t *data)
{
	char *t = NULL;
	list_t *node = NULL;
	int j;

	j = 0;
	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			alias_prnt(node);
			node = node->nxt;
		}
		return (0);
	}
	for (j = 1; data->argv[j]; j++)
	{
		t = _sstrchr(data->argv[j], '=');
		if (t)
		{
			aliaset(data, data->argv[j]);
		}
		else
		{
			alias_prnt(initial_node(data->alias, data->argv[j], '='));
		}
	}
	return (0);
}
