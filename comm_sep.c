#include "shell.h"

/**
 * hsh - the shell loop for main
 * @data: a struct of parameter and return data
 * @argvc: the main's argument vector
 * Return: success 0, onerror or error code 1
*/
int hsh(data_t *data, char **argvc)
{
	ssize_t m;
	int ret_bltin;

	m = 0;
	ret_bltin = 0;

	while (m != -1 && ret_bltin != -2)
	{
		data_clear(data);
		if (interactive(data))
			_sputs("$ ");
		_sputchar(BUFF_FLUSH);
		m = feed_get(data);
		if (m != -1)
		{
			data_set(data, argvc);
			ret_bltin = bltin_get(data);
			if (ret_bltin == -1)
				cmd_seek(data);
		}
		else if (interactive(data))
			_sputchar('\n');
		data_free(data, 0);
	}
	hist_wrt(data);
	data_free(data, 1);
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
		if (execve(data->path, data->argv, shllget_env(data)) == -1)
		{
			data_free(data, 1);
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
	    {"setenv", shllunset_env},
	    {"env", shll_env},
	    {"unsetenv", shllunset_env},
	    {"exit", shll_exit},
	    {"cd", shll_cd},
	    {"help", shll_hlp},
	    {"history", shll_hist},
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
 * shll_cd - alters the current working directory
 * @data: a struct of potential arguments
 * Return: 0 always
*/
int shll_cd(data_t *data)
{
	int retchng_dir;
	char *p, *d, buf[1024];

	p = getcwd(buf, 1024);
	if (p == NULL)
		_sputs("cwd failure msg\n");
	if (data->argv[1] == NULL)
	{
		d = shll_getenv(data, "HOME=");
		if (d == NULL)
			retchng_dir =
			    chdir((d = shll_getenv(data, "PWD=")) ? d : "/");
		else
			retchng_dir = chdir(d);
	}
	else if (_sstrcmp(data->argv[1], "-") == 0)
	{
		if (!shll_getenv(data, "OLDPWD="))
		{
			_sputs(p);
			_sputchar('\n');
			return (1);
		}
		_sputs(shll_getenv(data, "OLDPWD=")), _sputchar('\n');
		retchng_dir =
		    chdir((d = shll_getenv(data, "OLDPWD=")) ? d : "/");
	}
	else
		retchng_dir = chdir(data->argv[1]);
	if (retchng_dir == -1)
	{
		err_print(data, "Cannot CD into ");
		_errputs(data->argv[1]), errputchar('\n');
	}
	else
	{
		shllset_env(data, "OLDPWD", shll_getenv(data, "PWD="));
		shllset_env(data, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * shll_hlp - invokes the help directory
 * @data: a struct of potential arguments
 * Return: 0 always
*/
int shll_hlp(data_t *data)
{
	char **arr_arg;

	arr_arg = data->argv;
	_sputs("Implementing help function");
	if (0)
		_sputs(*arr_arg);
	return (0);
}
