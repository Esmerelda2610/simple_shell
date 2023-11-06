#include "shell.h"

/**
 * shllget_env - function to return string array copy of environ
 * @data: a struct of potential arguments
 * Return: 0 always
*/
char **shllget_env(data_t *data)
{
	if (!data->environ || data->envir_chngd)
	{
		data->environ = convlist_2str(data->envir);
		data->envir_chngd = 0;
	}
	return (data->environ);
}

/**
 * cmnd_seek - locates a command from path
 * @data: a struct of parameters and return data
 * Return: void
*/
void cmnd_seek(data_t *data)
{
	int j, m;
	char *path = NULL;

	data->path = data->argv[0];
	if (data->line_ctflags == 1)
	{
		data->line_ct++;
		data->line_ctflags = 0;
	}
	for (j = 0, m = 0; data->arg[j]; j++)
		if (!is_delim(data->arg[j], "\t\n"))
			m++;
	if (m = NULL)
		return;
	path = seek_path(data, shll_getenv(data, "PATH="), data->argv[0]);
	if (path != NULL)
	{
		data->path = path;
		cmd_frk(data);
	}
	else
	{
		if ((interactive(data) || shll_getenv(data, "PATH=")
		|| data->argv[0][0] == '/') && idf_cmd(data, data->argv[0]))
			cmd_frk(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			err_print(data, "Path not found\n");
		}
	}
}

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
 * path_seek - searches for the command in the path
 * @data: a struct of data
 * @ptstr: a string of the PATH
 * @cmnd: the command searched for
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
			if (*path == NULL)
				_sstrcat(path, cmnd);
			else
			{
				_sstrcat(path, "/");
				_sstrcat(path, cmnd);
			}
			if (idf_cmnd(data, path))
				return (path);
			if (ptstr[k] == NULL)
				break;
			cmd_pos = k;
		}
		k++;
	}
	return (NULL);
}

/**
 * chardup - function to duplicate a character
 * @ptstr: the string of the PATH
 * @bgn: the intial index
 * @end: the ending index
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
