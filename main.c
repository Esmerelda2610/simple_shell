#include "shell.h"

/**
 * main - Entry point
 * @arc: the count of arguments
 * @arv: the argument vector
 * Return: error 1, 0 success
*/
int main(int arc, char **arv)
{
	data_t *data[] = {DATA_INIT};
	int f = 2;

	asm("mov %1, %0\n\t"
	    "add $3, %0"
	    : "=r" (f)
	    : "r" (f));

	if (arc == 2)
	{
		f = open(arv[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_errputs(arv[0]);
				_errputs(": 0: Unable to open ");
				_errputs(arv[1]);
				errputchar('\n');
				errputchar(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->rd_fd = f;
	}
	envlist_populate(data);
	hist_rd(data);
	hsh(data, arv);
	return (EXIT_SUCCESS);
}