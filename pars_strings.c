#include "shell.h"

/**
 * idf_cmnd - checks if a file is an exe ccommand
 * @data: a struct of data
 * @path: the file path
 * Return: the executable file
*/
int idf_cmnd(data_t *data, char *path)
{
	struct stat sb;

	(void)data;
	if (stat(path, &sb) == -1)
		return (0);

	return (S_ISREG(sb.st_mode) && (sb.st_mode & S_IXUSR));
}

/**
 * chardup - function to duplicate a character
 * @ptstr: the string of the PATH
 * @bgn: the intial index
 * @end: the ending index
 * Return: the buffer
 */

char *chardup(char *ptstr, int bgn, int end)
{
	int j = 0, m = 0;
	static char buffer[1024];

	for (m = 0, j = bgn; j < end; j++)
		if (ptstr[j] != ':')
			buffer[m++] = ptstr[j];
	buffer[m] = 0;
	return (buffer);
}

/**
 * path_seek - searches for the command in the path
 * @data: a struct of data
 * @ptstr: a string of the PATH
 * @cmnd: the command searched for
 * Return: NULL
*/
char *path_seek(data_t *data, char *ptstr, char *cmnd)
{
	char *path;
	int k = 0, cmd_pos = 0;

	if (ptstr == NULL)
		return (NULL);
	if ((_sstrlen(cmnd) > 2) && pre_substr(cmnd, "./"))
	{
		if (idf_cmnd(data, cmnd))
			return (cmnd);
	}
	while (1)
	{
		if (!ptstr[k] || ptstr[k] == ':')
		{
			path = chardup(ptstr, cmd_pos, k);
			if (!*path)
				_sstrcat(path, cmnd);
			else
			{
				_sstrcat(path, "/");
				_sstrcat(path, cmnd);
			}
			if (idf_cmnd(data, path))
				return (path);
			if (!ptstr[k])
				break;
			cmd_pos = k;
		}
		k++;
	}
	return (NULL);
}

