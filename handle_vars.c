#include "shell.h"

/**
 * chain_delim - function to test if char in chain is a delimitor
 * @data: a struct of parameters
 * @bff: the buffer of the character
 * @pd: the current position address in the buffer
 * Return: 0 always
*/
int chain_delim(data_t *data, char *bff, size_t *pd)
{
	size_t k = *pd;

	if (bff[k + 1] == '|' && bff[k] == '|')
	{
		bff[k] = 0;
		k++;
		data->cmdbuff_type = CMMND_OR;
	}
	else if (bff[k + 1] == '&' && bff[k] == '&')
	{
		bff[k] = 0;
		k++;
		data->cmdbuff_type = CMMND_AND;
	}
	else if (bff[k] == ';')
	{
		bff[k] = 0;
		data->cmdbuff_type = CMMND_CHAIN;
	}
	else
	{
		return (0);
	}
	*pd = k;
	return (1);
}

/**
 * chk_chain - checks based on last status
 * @data: a struct of parameters
 * @bff: a buffer for the character
 * @b: the buffer's current position address
 * @j: the initial position in the buffer
 * @length: the buffer length
 */
void chk_chain(data_t *data, char *bff, size_t *b, size_t j, size_t length)
{
	size_t k = *b;

	if (data->cmdbuff_type == CMMND_AND)
	{
		if (data->status)
		{
			bff[j] = 0;
			k = length;
		}
	}
	if (data->cmdbuff_type == CMMND_OR)
	{
		if (!data->status)
		{
			bff[j] = 0;
			k = length;
		}
	}
	*b = k;
}

/**
 * chng_alias - replaces alias in tokenized string
 * @data: a struct of parameters
 * Return: if replaced 1, otherwise 0
*/
int chng_alias(data_t *data)
{
	list_t *nd;
	char *b;
	int j;

	for (j = 0; j < 10; j++)
	{
		nd = initial_node(data->alias, data->argv[0], '=');
		if (nd == NULL)
			return (0);
		free(data->argv[0]);
		b = _sstrchr(nd->str, '=');
		if (b == NULL)
			return (0);
		b = _sstrdup(b + 1);
		if (b == NULL)
			return (0);
		data->argv[0] = b;
	}
	return (1);
}

/**
 * intchnge_vars - function to replace variables
 * in tokenized string
 * @data: a struct of arguments
 * Return: if successful 1, otherwise 0
*/
int intchnge_vars(data_t *data)
{
	list_t *nd;
	int k = 0;

	for (k = 0; data->argv[k]; k++)
	{
		if (data->argv[k][0] != '$' || !data->argv[k][1])
			continue;
		if (!_sstrcmp(data->argv[k], "$?"))
		{
			intchnge_str(&(data->argv[k]),
				     _sstrdup(digit_convrt(data->status, 10, 0)));
			continue;
		}
		if (!_sstrcmp(data->argv[k], "$$"))
		{
			intchnge_str(&(data->argv[k]),
				     _sstrdup(digit_convrt(getpid(), 10, 0)));
			continue;
		}
		nd = initial_node(data->envir, &data->argv[k][1], '=');
		if (nd != NULL)
		{
			intchnge_str(&(data->argv[k]),
				     _sstrdup(_sstrchr(nd->str, '=') + 1));
			continue;
		}
		intchnge_str(&data->argv[k], _sstrdup(""));
	}
	return (0);
}

/**
 * intchnge_str - function to replace a string
 * @old_str: the old string address
 * @new_str: the new string
 * Return: 1 for success
*/
int intchnge_str(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}
