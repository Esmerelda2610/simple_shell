#include "shell.h"

/**
 * handle_sigint - function to block ctrl-c
 * @sig_digi: a digit signal
 * Return: void
*/
void handle_sigint(__attribute__((unused))int sig_digi)
{
	_sputs("\n");
	_sputs("$ ");
	_sputs(BUFF_FLUSH);
}

/**
 * get_feed - function to get line less the newline
 * @data: a struct of parameters
 * Return: the read bytes
*/
ssize_t get_feed(data_t *data)
{
	static size_t k, m, length;
	static char *buff;
	char **buffp = &(data->arg), *b;
	ssize_t n = 0;

	_sputchar(BUFF_FLUSH);
	n = buffeed(data, &buff, &length);
	if (n == -1)
		return (-1);
	if (length != NULL)
	{
		m = k;
		b = buff + k;

		chk_chain(data, buff, &m, k, length);
		while (m < length)
		{
			if (idf_chain(data, buff, &m))
				break;
			k++;
		}
		k = m + 1;
		if (k >= length)
		{
			k = length = 0;
			data->cmdbuff_type = CMMND_NORM;
		}
		buffp = b;
		return (_sstrlen(b));
	}
	*buffp = buff;
	return (n);
}

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
		if (data->status == NULL)
		{
			bff[j] = 0;
			k = length;
		}
	}
	*b = k;
}
