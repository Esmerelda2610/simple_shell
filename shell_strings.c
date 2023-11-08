#include "shell.h"

/**
 * _sstrlen - calculates string length
 * @d: the string to whose length is measured
 * Return: string length
*/

int _sstrlen(char *d)
{
	int length = 0;
	if (!d)
		return (0);
	while (*d++)
	{
		length++;
	}
	return (length);
}

/**
 * _sstrcmp - function that compares two strings
 * @str1: the first string
 * @str2: the second string
 * Return: if str1 == str2 0, if str1 > str2 positive
 * if str1 < str2 negative
*/

int _sstrcmp(char *str1, char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

/**
 * pre_substr - checks if string starts with the substring
 * @str: the string to be searched
 * @sub_str: the substring searched for
 * Return: the address of the character after str, otherwise NULL
*/

char *pre_substr(const char *str, const char *sub_str)
{
	while (*sub_str)
		if (*sub_str++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * _sstrcat - function that concatenates two strings
 * @dest: the buffer destination
 * @src: the buffer source
 * Return: a pointer to the buffer destination
*/

char *_sstrcat(char *dest, char *src)
{
	char *ptr = dest + _sstrlen(dest);

	while (*src != '\0')
		*ptr++ = *src++;

	*ptr = '\0';

	return (dest);
}

/**
 * _sstrcpy - function that copies a string
 * @dest: the buffer destination
 * @src: the buffer source
 * Return: a pointer to the buffer destination
*/

char *_sstrcpy(char *dest, char *src)
{
	char *ptr = dest;

	while (*src != '\0')
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';

	return (dest);
}

