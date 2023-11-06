#include "shell.h"

/**
 * shll_hist - function to display the shell history
 * @data: a struct of potential arguments
 * 0 always
*/
int shll_hist(data_t *data)
{
	list_prnt(data->hist);
	return (0);
}