#include "shell.h"

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
	size_t k;

	k = *b;

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
