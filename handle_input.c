#include "shell.h"

/**
 * clear_feed - function to initialize the data_t struct
 * @data: the address of the struct
 */
void clear_feed(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

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
		data->argv = split_str(data->arg, " \t");
		if (!data->argv)
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

		chng_alias(data);
		intchnge_vars(data);
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
		if (!data->cmdbuff)
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
