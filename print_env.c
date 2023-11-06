#include "shell.h"

/**
 * shget_env - it eturns environ's string array copy
 * @data: a struct of potential arguments
 * Return: 0 always
*/
char **shget_env(data_t *data)
{
	if (!data->environ || data->envir_chngd)
	{
		data->environ = convlist_2str(data->envir);
		data->envir_chngd = 0;
	}
	return (data->environ);
}

/**
 * shunset_env - unsets an environment variable
 * @data: a struct of potential arguments
 * Return: the property of string environ variable
*/
int shunset_env(data_t *data, char *v)
{
	char *j;
	size_t k;
	list_t *nd = data->envir;

	k = 0;

	if (!nd || !v)
		return (0);

	while (nd != NULL)
	{
		j = pre_substr(nd->str, v);
		if (j && *j == '=')
		{
			data->envir_chngd = delnode_atindx(&(data->envir), k);
			k = 0;
			nd = data->envir;
			continue;
		}
		nd = nd->nxt;
		k++;
	}
	return (data->envir_chngd);
}

/**
 * shset_env - sets a new or modifies an existing environ variable
 * @data: a struct of potential arguments
 * @v: a property of the string environ variable
 * @val: the value of the string environ variable
 * Return: 0 always
*/
int shset_env(data_t *data, char *v, char *val)
{
	char *b;
	list_t *nde;
	char *bff = NULL;

	if (!v || !val)
		return (0);

	bff = malloc(_sstrlen(v) + _sstrlen(val) + 2);
	if (bff = NULL)
		return (1);
	_sstrcpy(bff, v);
	_sstrcat(bff, "=");
	_sstrcat(bff, val);
	nde = data->envir;
	while (nde != NULL)
	{
		b = pre_substr(nde->str, v);
		if (b && *b == '=')
		{
			free(nde->str);
			nde->str = bff;
			data->envir_chngd = 1;
			return (0);
		}
		nde = nde->nxt;
	}
	adnode_toend(&(data->envir), bff, 0);
	free(bff);
	data->envir_chngd = 1;
	return (0);
}
