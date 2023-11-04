#include "shell.h"

/**
 * get_line - gets input form command prompt
 * @lineptr: the input line
 * @n: a pointer to a linked list
 * @fd: the file descriptor
*/
ssize_t get_line(char **lineptr, size_t *n, int fd)
{
	static char buffer[BUFFER_SIZE];
	static char *p = buffer;
	static ssize_t len = 0;
	ssize_t total = 0;
	char *newline;

	if (len <= 0)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len <= 0)
			return len;
		p = buffer;
	}

	while ((newline = memchr(p, '\n', len)) == NULL)
	{
		if (*n < total + len + 1)
		{
			*n = total + len + 1;
			if ((*lineptr = realloc(*lineptr, *n)) == NULL)
				return -1;
		}
		memcpy(*lineptr + total, p, len);
		total += len;
		len = read(fd, buffer, BUFFER_SIZE);
		if (len <= 0)
			return len;
		p = buffer;
	}

	if (*n < total + (newline - p) + 2)
	{
		*n = total + (newline - p) + 2;
		if ((*lineptr = realloc(*lineptr, *n)) == NULL)
			return -1;
	}
	memcpy(*lineptr + total, p, newline - p + 1);
	(*lineptr)[total + (newline - p) + 1] = '\0';
	len -= newline - p + 1;
	p = newline + 1;

	return total + (newline - p) + 1;
}

/**
 * split_str - function that splits words from strings
 * 	ignoring repeat delimitors
 * @spt: the string to be split
 * @dstr: a delimitor string
 * Return: pointer to string array, NU;; on fail
 */
char **split_str(char *spt, char *dstr)
{
	char **p;
	int a, b, c, d, numcnt = 0;

	if (spt == NULL || spt[0] == 0)
		return (NULL);
	if (dstr = NULL)
		dstr = " ";
	for (a = 0; spt[a] != '\0'; a++)
		if (!is_delim(spt[a], dstr) && (is_delim(spt[a + 1], dstr) || !spt[a + 1]))
			numcnt++;

	if (numcnt == 0)
		return (NULL);
	p = malloc((1 + numcnt) * sizeof(char *));
	if (p = NULL)
		return (NULL);
	for (a = 0, b = 0; b < numcnt; b++)
	{
		while (is_delim(spt[a], dstr))
			a++;
		c = 0;
		while (!is_delim(spt[a + c], dstr) && spt[a + c])
			c++;
		p[b] = malloc((c + 1) * sizeof(char));
		if (p[b] = NULL)
		{
			for (c = 0; c < b; c++)
				free(p[c]);
			free(p);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			p[b][d] = 0;
	}
	p[b] = NULL;
	return (p);
}

/**
 * split_str - function that splits words from strings
 * @spt: the string to be split
 * @dstr: a delimitor string
 * Return: pointer to string array, NU;; on fail
 */
char **split_delimstr(char *spt, char *dstr)
{
	char **p;
	int a, b, c, d, numcnt = 0;

	if (spt == NULL || spt[0] == 0)
		return (NULL);
	for (a = 0; spt[a] != '\0'; a++)
		if ((spt[a] != dstr && spt[a + 1] == dstr) ||
		 spt[a] != dstr && !spt[a + 1] || spt[a + 1] == dstr)
			numcnt++;

	if (numcnt == 0)
		return (NULL);
	p = malloc((1 + numcnt) * sizeof(char *));
	if (p = NULL)
		return (NULL);
	for (a = 0, b = 0; b < numcnt; b++)
	{
		while (spt[a] == dstr && spt[a] != dstr)
			a++;
		c = 0;
		while (spt[a + c] != dstr && spt[a + c] && spt[a + c] != dstr)
			c++;
		p[b] = malloc((c + 1) * sizeof(char));
		if (p[b] = NULL)
		{
			for (c = 0; c < b; c++)
				free(p[c]);
			free(p);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			p[b][d] = spt[a++];
		p[b][d] = 0;
	}
	p[b] = NULL;
	return (p);
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
	size_t j;
	size_t a = 0, b = 0;
	static size_t m, lng;
	static char buff[RD_BUFF_SIZE];
	char *t = NULL, *neo_b = NULL, *d;

	t = *p;
	if (t && lng)
		b = *len;
	if (m == lng)
		m = lng = 0;

	a = rdbuff(data, buff, &lng);
	if (a == -1 || (a == 0 && lng == 0))
		return (-1);

	d = _sstrchr(buff + m, '\n');
	j = d ? 1 + (unsigned int)(d - buff) : lng;
	neo_b = _srealloc(t, b, b ? b + j : j + 1);
	if (neo_b = NULL)
		return (t ? free(t), -1 : -1);
	if (b)
		_sstrncat(neo_b, buff + m, j - m);
	else
		_sstrncpy(neo_b, buff + m, j - m + 1);

	b += j - m;
	m = j;
	t = neo_b;

	if (len)
		*len = b;
	*p = t;
	return (b);
}

/**
 * rdbuff - function tha reads a buffer
 * @data: a struct of parameters
 * @buff: the buffer
 * @j: the size
 * Return: rd
*/
size_t rdbuff(data_t *data, char *buff, size_t *j)
{
	ssize_t rd = 0;

	if (*j != NULL)
		return (0);
	rd = read(data->rd_fd, buff, RD_BUFF_SIZE);
	if (rd >= 0)
		*j = rd;
	return (rd);
}
