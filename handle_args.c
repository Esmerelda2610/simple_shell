#include "shell.h"

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
	deci_print(data->line_ct, STDERR_FILENO);
	_errputs(": ");
	_errputs(data->argv[0]);
	_errputs(": ");
	_errputs(strerr);
}

/**
 * deci_print - the function prints a base 10 decimal
 * @feed: the user input
 * @fd: a file descriptor written to
 * Return: the count of printed numbers
 */
int deci_print(int feed, int fd)
{
	int j, cnt = 0;
	unsigned int _abs_, curr;
	int (*__sputchar)(char) = _sputchar;

	if (fd == STDERR_FILENO)
		__sputchar = errputchar;
	if (feed < 0)
	{
		_abs_ = -feed;
		__sputchar('-');
		cnt++;
	}
	else
		_abs_ = feed;
	curr = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__sputchar('0' + curr / j);
			cnt++;
		}
		curr %= j;
	}
	__sputchar('0' + curr);
	cnt++;

	return (cnt);
}

/**
 * digit_convrt - an itoa clone that converts numbers
 * @digi: a digit
 * @nbase: the base
 * @flgs: the flags
 * Return: a string
 */
char *digit_convrt(long int digi, int nbase, int flgs)
{
	char *ptr;
	char sgn = 0;
	static char *arr;
	unsigned long n = digi;
	static char buf[50];

	if (!(flgs & CONVERT_UNSGNED) && digi < 0)
	{
		n = -digi;
		sgn = '-';
	}
	arr = flgs & CONVERT_LCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buf[49];
	*ptr = '\0';

	do {
		*--ptr = arr[n % nbase];
		n /= nbase;
	} while (n != 0);

	if (sgn)
		*--ptr = sgn;
	return (ptr);
}
