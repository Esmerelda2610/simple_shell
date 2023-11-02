#include "shell.h"

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
