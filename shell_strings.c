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
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
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
 * @des: the buffer destination
 * @src: the buffer source
 * Return: a pointer to the buffer destination
*/

char *_sstrcat(char *des, char *src)
{
	char *ptr = des;

	while (*des)
		des++;
	while (*src)
		*des++ = *src++;
	*des = *src;
	return (ptr);
}

/**
 * _sstrcpy - function that copies a string
 * @des: the buffer destination
 * @sce: the buffer source
 * Return: a pointer to the buffer destination
*/

char *_sstrcpy(char *des, char *sce)
{
	int j = 0;

	if (des == sce || sce == 0)
		return (des);
	while (sce[j])
	{
		des[j] = sce[j];
		j++;
	}
	des[j] = 0;

	return (des);
}
