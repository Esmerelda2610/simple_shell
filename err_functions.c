#include "shell.h"

/**
 * _errputs - function that prints an input string
 * @str: the printed input string
 * Return: nada
*/
void _errputs(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

/**
 * errputchar - prints the c character to stderr
 * @c: the printed character
 * Return: 1 on success, -1 on error and set appropriately
*/
int errputchar(char c)
{
	static int j;
	static char buff[WRT_BUFF_SIZE];

	if (c == BUFF_FLUSH || j >= WRT_BUFF_SIZE)
	{
		write(2, buff, j);
		j = 0;
	}
	if (c != BUFF_FLUSH)
		buff[j++] = c;
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
	static int j;
	static char buff[WRT_BUFF_SIZE];

	if (c == BUFF_FLUSH || j >= WRT_BUFF_SIZE)
	{
		write(fd, buff, j);
		j = 0;
	}
	if (c != BUFF_FLUSH)
		buff[j++] = c;
	return (1);
}

/**
 * _putstrfd - function that prints an input string
 * @str: string to print
 * @fd: the file descriptor written to
 * Return: the input string
*/
int _putstrfd(char *str, int fd)
{
	int j;

	if (str == NULL)
		return (0);
	while (*str)
	{
		j += _putstrfd(*str++, fd);
	}
	return (j);
}

/**
 * err_print - function to print error message
 * @data: struct parameters and return data
 * @strerr: the string with specific error type
 * Return: if no numbers or string 0, otherwise converted number on error -1
*/
void err_print(data_t *data, char *strerr)
{
	_errputs(data->pname);
	_errputs(": ");
	dprint(data->line_ct, STDERR_FILENO);
	_errputs(": ");
	_errputs(data->argv[0]);
	_errputs(": ");
	_errputs(strerr);
}
