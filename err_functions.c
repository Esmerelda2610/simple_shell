#include "shell.h"

/**
 * _errputs - function that prints an input string
 * @s: the printed input string
 * Return: nada
*/
void _errputs(char *s)
{
	int k;

	k = 0;
	if (s == NULL)
	{
		return;
	}
	while (s[k] != '\0')
	{
		_sputchar(s[k]);
		s++;
	}
}

/**
 * errputchar - prints the c character to stderr
 * @c: the printed character
 * Return: 1 on success, -1 on error and set appropriately
*/
int errputchar(char c)
{
	static char buff[WRT_BUFF_SIZE];
	static int j;

	if (c == BUFF_FLUSH || j >= WRT_BUFF_SIZE)
	{
		write(2, buff, j);
		j = 0;
	}
	if (c != BUFF_FLUSH)
	{
		buff[j++] = c;
	}
	return (1);
}

/**
 * _sputs_fd - function that writes the character c to fd
 * @c: the printed character
 * @fd: the file descriptor
 * Return: 1 on success, -1 on error and set appropriately
*/
int _sputs_fd(char c, int fd)
{
	static char buff[WRT_BUFF_SIZE];
	static int j;

	if (c == BUFF_FLUSH || j >= WRT_BUFF_SIZE)
	{
		write(fd, buff, j);
		j = 0;
	}
	if (c != BUFF_FLUSH)
	{
		buff[j++] = c;
	}
	return (1);
}

/**
 * _putstrfd - function that prints an input string
 * @s: string to print
 * @fd: the file descriptor written to
 * Return: the input string
*/
int _putstrfd(char *s, int fd)
{
	int j;

	if (s == NULL)
	{
		return (0);
	}
	while (*s)
	{
		j += _sputs_fd(*s++, fd);
	}
	return (j);
}

