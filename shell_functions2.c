#include "shell.h"

/**
 * str_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: the converted string
*/

int str_to_int(char *s)
{
	int result = 0;
	bool isNegative = false;

	if (*s == '-')
	{
		isNegative = true;
		s++;
	}

	while (*s)
	{
		if (*s >= '0' && *s <= '9')
		{
			result = result * 10 + (*s - '0');
		}
		else
		{
			break;
		}
		s++;
	}

	if (isNegative)
	{
		result = -result;
	}

	return (result);
}

/**
 * is_alphab - function that checks if input is an alphabet
 * @c: the character checked
 * Return: 1 if is an alphabet, otherwise 0
*/

int is_alphab(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * is_delim - function that checks if character is a delim
 * @delim: the delimeter string
 * @c: the charcter to be checked
*/

int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (c == *delim)
		{
			return (1);
		}
		delim++;
	}
	return (0);
}

/**
 * interactive - if shell is interactive it returns true
 * @data: the address of struct
 * Return: if in interactive mode 1, otherwise 0
*/

int interactive(data_t *data)
{
	return (issaty(STDIN_FILENO) && data->read_fd <= 2);
}

/**
 * _sstrchr - finds a character in a string
 * @s: the string searched
 * @c: the character searched for
 * Return: NULL
*/
char *_sstrchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	return (NULL);
}
