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
