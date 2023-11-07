#include "shell.h"

/**
 * detach_comments - replaces the first instance of # with \0
 * @bff: the address of string to modify
 * Return: 0 always
*/
void detach_comments(char *bff)
{
	int j;

	for (j = 0; bff[j] != '\0'; j++)
		if (bff[j] == '#' && (!j || bff[j - 1] == ' '))
		{
			bff[j] = '\0';
			break;
		}
}

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

	if (bff[k] == '|' && bff[k + 1] == '|')
	{
		bff[k] = 0;
		k++;
		data->cmdbuff_type = CMMND_OR;
	}
	else if (bff[k] == '&' && bff[k + 1] == '&')
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
		return (0);
	*pd = k;
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
	int k;

	k = 0;

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
