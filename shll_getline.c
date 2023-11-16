#include "shell.h"

/**
 * buffeed - funtion to buffer chained commands
 * @data: a struct of parameters
 * @bff: the buffer address
 * @length: the address of the length variable
 * Return: the read bytes
*/
ssize_t buffeed(data_t *data, char **bff, size_t *length)
{
	size_t m = 0;
	size_t ln_p = 0;

	if (!*length)
	{
		free(*bff);
		*bff = NULL;
		signal(SIGINT, handle_sigint);
#if USE_GETLINE
{
		m = getline(bff, &ln_p, stdin);
}
#else
{
		m = shll_getline(data, bff, &ln_p);
}
#endif
		if (m > 0)
		{
			if ((*bff)[m - 1] == '\n')
			{
				(*bff)[m - 1] = '\0';
				m--;
			}
			data->line_ctflags = 1;
			detach_comments(*bff);
			histlist_build(data, *bff, data->hist_ct++);
			{
				*length = m;
				data->cmdbuff = bff;
			}
		}
	}
	return (m);
}

/**
 * get_feed - function to get line less the newline
 * @data: a struct of parameters
 * Return: the read bytes
 */
ssize_t get_feed(data_t *data)
{
	static char *buff;
	static size_t k, m, length;
	ssize_t n;
	char **buffp = &(data->arg), *b;

	n = 0;
	_sputchar(BUFF_FLUSH);
	n = buffeed(data, &buff, &length);
	if (n == -1)
	{
		return (-1);
	}
	if (length)
	{
		m = k;
		b = buff + k;

		chk_chain(data, buff, &m, k, length);
		while (m < length)
		{
			if (chain_delim(data, buff, &m))
			{
				break;
			}
			m++;
		}
		k = m + 1;
		if (k >= length)
		{
			k = length = 0;
			data->cmdbuff_type = CMMND_NORM;
		}
		*buffp = b;
		return (_sstrlen(b));
	}
	*buffp = buff;
	return (n);
}

/**
 * bufread - function to read a buffer
 * @data: a struct of parameters
 * @bff: the buffer
 * @j: the read size
 * Return: m
 */
ssize_t bufread(data_t *data, char *bff, size_t *j)
{
	ssize_t m;

	m = 0;
	if (*j)
	{
		return (0);
	}
	m = read(data->rd_fd, bff, RD_BUFF_SIZE);
	if (m >= 0)
	{
		*j = m;
	}
	return (m);
}

/**
 * shll_getline - retrieves next line from standard input
 * @data: a struct of parameters
 * @p: a preallocated or NULL pointer's buffer address
 * @len: the preallocated ptr buffer size
 * Return: b
 */
int shll_getline(data_t *data, char **p, size_t *len)
{

	static char buff[RD_BUFF_SIZE];
	static size_t m, ln;
	size_t j;
	ssize_t a = 0, b = 0;
	char *t = NULL, *neo_b = NULL, *d;

	t = *p;
	if (t && len)
	{
		b = *len;
	}
	if (m == ln)
		m = ln = 0;
	a = bufread(data, buff, &ln);
	if (a == -1 || (a == 0 && ln == 0))
		return (-1);
	d = _sstrchr(buff + m, '\n');
	j = d ? 1 + (unsigned int)(d - buff) : ln;
	neo_b = shll_realloc(t, b, b ? b + j : j + 1);
	if (!neo_b) /*if memory alloc fails*/
		return (t ? free(t), -1 : -1);
	if (b) /*if memory is allocated*/
	{
		_sstrncat(neo_b, buff + m, j - m);
	}
	else
	{
		_sstrncpy(neo_b, buff + m, j - m + 1);
	}
	b += j - m;
	m = j;
	t = neo_b;
	if (len)
		*len = b;
	*p = t;
	return (b);
}

/**
 * handle_sigint - function to block ctrl-c
 * @sig_digi: a digit signal
 * Return: void
 */
void handle_sigint(__attribute__((unused)) int sig_digi)
{
	_sputs("\n");
	_sputs("Liz&Josh$ ");
	_sputchar(BUFF_FLUSH);
}
