#include "shell.h"

/**
 * shll_getenv - retrieves value of an environ variable
 * @data: a struct of potential arguments
 * @nm: the env variable name
 * Return: value of env variable
*/
char *shll_getenv(data_t *data, const char *nm)
{
	list_t *nod = data->envir;
	char *b;

	while (nod)
	{
		b = pre_substr(nod->str, nm);
		if (b && *b)
			return (b);
		nod = nod->nxt;
	}
	return (NULL);
}

/**
 * shll_env - function that prints the current environment
 * @data: a struct of potential arguments
 * Return: 0 success
*/
int shll_env(data_t *data)
{
	listprnt_str(data->envir);
	return (0);
}

/**
 * shll_setenv - function that initializes a new
 * or modifies an existing environment variable
 * @data: a struct of potential arguments
 * Return: 0 success
*/
int shll_setenv(data_t *data)
{
	if (data->argc != 3)
	{
		_errputs("Improper number of arguments!\n");
		return (1);
	}
	if (shset_env(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * envlist_populate - function to populate the env linked list
 * @data: a struct of potential arguments
 * Return: 0 always
*/
int envlist_populate(data_t *data)
{
	size_t j;
	list_t *node = NULL;

	for (j = 0; environ[j]; j++)
		adnode_atend(&node, environ[j], 0);
	data->envir = node;
	return (0);
}

/**
 * shllunset_env - function to remove an env variable
 * @data: a struct of potential arguments
 * Return: 0 always
*/
int shllunset_env(data_t *data)
{
	int j;

	if (data->argc == 1)
	{
		_errputs("The arguments are too few!\n");
		return (1);
	}
	for (j = 1; j <= data->argc; j++)
		shunset_env(data, data->argv[j]);

	return (0);
}
