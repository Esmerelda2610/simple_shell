#include "shell.h"

/**
 * shll_exit - function to exit the shell
 * @data: a struct of potential argumments
 * Return: exits on (0) if data.argv[0] != "exit"
*/
int shll_exit(data_t *data)
{
	int chk_exit;

	if (data->argv[1])
	{
		chk_exit = atoi_errs(data->argv[1]);
		if (chk_exit == -1)
		{
			data->status = 2;
			err_print(data, "Number unknown: ");
			_errputs(data->argv[1]);
			errputchar('\n');
			return (1);
		}
		data->err_dig = atoi_errs(data->argv[1]);
		return (-2);
	}
	data->err_dig = -1;
	return (-2);
}

/**
 * shll_cd - alters the current working directory
 * @data: a struct of potential arguments
 * Return: 0 always
 */
int shll_cd(data_t *data)
{
	char *p, *dir, buf[1024];
	int retchng_dir;

	p = getcwd(buf, 1024);
	if (!p)
		_sputs("cwd failure msg\n");
	if (!data->argv[1])
	{
		dir = shll_getenv(data, "HOME=");
		if (!dir)
			retchng_dir =
			    chdir((dir = shll_getenv(data, "PWD=")) ? dir : "/");
		else
			retchng_dir = chdir(dir);
	}
	else if (_sstrcmp(data->argv[1], "-") == 0)
	{
		if (shll_getenv(data, "OLDPWD=") == NULL)
		{
			_sputs(p);
			_sputchar('\n');
			return (1);
		}
		_sputs(shll_getenv(data, "OLDPWD=")), _sputchar('\n');
		retchng_dir =
		    chdir((dir = shll_getenv(data, "OLDPWD=")) ? dir : "/");
	}
	else
		retchng_dir = chdir(data->argv[1]);
	if (retchng_dir == -1)
	{
		err_print(data, "Can't cd to ");
		_errputs(data->argv[1]), errputchar('\n');
	}
	else
	{
		shset_env(data, "OLDPWD", shll_getenv(data, "PWD="));
		shset_env(data, "PWD", getcwd(buf, 1024));
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
	{
		_sputs(*arr_arg);
	}
	return (0);
}

/**
 * shll_hist - function to display the shell history
 * @data: a struct of potential arguments
 * Return: 0 always
 */
int shll_hist(data_t *data)
{
	list_prnt(data->hist);
	return (0);
}
