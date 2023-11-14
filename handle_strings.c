#include "shell.h"

/**
 * interactive - if shell is interactive it returns true
 * @data: the address of struct
 * Return: if in interactive mode 1, otherwise 0
 */

int interactive(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->rd_fd <= 2);
}

/**
 * is_delim - function that checks if character is a delim
 * @delim: the delimeter string
 * @c: the charcter to be checked
 * Return: 0 always
 */

int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * is_alphab - function that checks if input is an alphabet
 * @c: the character checked
 * Return: 1 if is an alphabet, otherwise 0
 */

int is_alphab(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * str_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: the converted string
*/

int str_to_int(char *s)
{
	int j, flg, sn, opt;
	unsigned int rst;

	flg = 0;
	sn = 1;
	rst = 0;
	for (j = 0; s[j] != '\0' && flg != 2; j++)
	{
		if (s[j] == '-')
			sn *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			flg = 1;
			rst *= 10;
			rst += (s[j] - '0');
		}
		else if (flg == 1)
		{
			flg = 2;
		}
	}
	if (sn == -1)
	{
		opt = -rst;
	}
	else
	{
		opt = rst;
	}
	return (opt);
}
