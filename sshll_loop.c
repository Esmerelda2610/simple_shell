#include "shell.h"

/**
 * hsh - the shell loop for main
 * @data: a struct of parameter and return data
 * @argvc: the main's argument vector
 * Return: success 0, onerror or error code 1
*/
int hsh(data_t *data, char **argvc)
{
	ssize_t m = 0;
	int ret_bltin = 0;

	while (m != -1 && ret_bltin != -2)
	{
		clear_feed(data);
		if (interactive(data))
			_sputs("#\033[1;34mLiznJoshell\033[0m$ ");
		errputchar(BUFF_FLUSH);
		m = get_feed(data);
		if (m != -1)
		{
			set_feed(data, argvc);
			ret_bltin = bltin_seek(data);
			if (ret_bltin == -1)
				cmnd_seek(data);
		}
		else if (interactive(data))
			_sputchar('\n');
		free_feed(data, 0);
	}
	hist_wr(data);
	free_feed(data, 1);
	if (!interactive(data) && data->status)
		exit(data->status);
	if (ret_bltin == -2)
	{
		if (data->err_dig == -1)
			exit(data->status);
		exit(data->err_dig);
	}
	return (ret_bltin);
}

/**
 * bltin_seek - locates a builtin command
 * @data: a struct of parameters and return data
 * Return: succesful exe 0, found builtin but failed 1
 * builtin not foune -1, builtin signals exit -2
 */
int bltin_seek(data_t *data)
{
	int j, retblt_in = -1;
	tab_shllbuiltin bltin_tbl[] = {
	    {"exit", shll_exit},
	    {"env", shll_env},
	    {"help", shll_hlp},
	    {"history", shll_hist},
	    {"setenv", shll_setenv},
	    {"unsetenv", shllunset_env},
	    {"cd", shll_cd},
	    {"alias", shll_alias},
	    {NULL, NULL}
	};

	for (j = 0; bltin_tbl[j].type; j++)
		if (_sstrcmp(data->argv[0], bltin_tbl[j].type) == 0)
		{
			data->line_ct++;
			retblt_in = bltin_tbl[j].funct(data);
			break;
		}
	return (retblt_in);
}

/**
 * cmnd_seek - locates a command from path
 * @data: a struct of parameters and return data
 * Return: void
 */
void cmnd_seek(data_t *data)
{
	char *path = NULL;
	int j, m;

	data->path = data->argv[0];
	if (data->line_ctflags == 1)
	{
		data->line_ct++;
		data->line_ctflags = 0;
	}
	for (j = 0, m = 0; data->arg[j]; j++)
		if (!is_delim(data->arg[j], "\t\n"))
			m++;
	if (!m)
		return;
	path = path_seek(data, shll_getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		cmd_frk(data);
	}
	else
	{
		if ((interactive(data) || shll_getenv(data, "PATH=") || data->argv[0][0] == '/') && idf_cmnd(data, data->argv[0]))
			cmd_frk(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			err_print(data, "Path not found\n");
		}
	}
}



/**
 * cmd_frk - function to fork an execute thread
 * @data: a struct of parameters
 * Return: void
*/
void cmd_frk(data_t *data)
{
	pid_t pid_ch;

	pid_ch = fork();
	if (pid_ch == -1)
	{
		perror("Error: ");
		return;
	}
	if (pid_ch == 0)
	{
		if (execve(data->path, data->argv, shget_env(data)) == -1)
		{
			free_feed(data, 1);
			if (errno == EACCES)

				exit(126);
			exit(1);

		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				err_print(data, "Permission has been denied\n");
		}
	}
}
