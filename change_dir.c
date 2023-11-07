#include "shell.h"

/**
 * set_feed - function to initialize the data struct
 * @data: the address of the struct
 * @argvc: an argument vector
*/
void set_feed(data_t *data, char **argvc)
{
	int j;

	j = 0;

	data->pname = argvc[0];
	if (data->arg)
	{
		data->argv = split_str(data->arg, "\t");
		if (data->argv == NULL)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _sstrdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (j = 0; data->argv && data->argv[j]; j++)
			;
		data->argc = j;

		intchnge_vars(data);
		chng_alias(data);
	}
}

/**
 * free_feed - function to free data_t struct fields
 * @data: the address of the struct
 * @fields: if freeing all fields, true
*/
void free_feed(data_t *data, int fields)
{
	free_str(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (fields)
	{
		if (data->cmdbuff_type == NULL)
			free(data->arg);
		if (data->envir)
			freelnkd_list(&(data->envir));
		if (data->hist)
			freelnkd_list(&(data->hist));
		if (data->alias)
			freelnkd_list(&(data->alias));
		free_str(data->environ);
			data->environ = NULL;
			free_ptr((void **)data->cmdbuff);
		if (data->rd_fd > 2)
			close(data->rd_fd);
		_sputchar(BUFF_FLUSH);
	}
}

/**
 * clear_feed - function to initialize the data_t struct
 * @data: the address of the struct
*/
void clear_feed(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = NULL;
}

/**
 * addnode_atend - attaches a new node at the nd of list
 * @h: head node pointer's address
 * @s: the node field string
 * @dig: an index of the node in history
 * Return: the address of the new node
*/
list_t *addnode_atend(list_t **h, const char *s, int dig)
{
	list_t *new, *nd;

	if (h == NULL)
		return (NULL);

	nd = *h;
	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	set_mem((void *)new, 0, sizeof(list_t));
	new->dig = dig;
	if (s != NULL)
	{
		new->str = _sstrdup(s);
		if (new->str == NULL)
		{
			free(new);
			return (NULL);
		}
	}
	if (nd != NULL)
	{
		while (nd->nxt)
			nd = nd->nxt;
		nd->nxt = new;
	}
	else
		*h = new;
	return (new);
}
