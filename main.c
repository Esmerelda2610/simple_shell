#include "shell.h"

/**
 * main - Entry point
 * @arc: the count of arguments
 * @arv: the argument vector
 * Return: error 1, 0 success
*/
int main(int ac, char **av)
{
	data_t data[] = { DATA_INIT };
	int f;

	f = 2;
	asm("mov %1, %0\n\t"
	    "add $3, %0"
	    : "=r" (f)
	    : "r" (f));

	if (ac == 2)
	{
		f = open(av[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
			{
				exit(126);
			}
			if (errno == ENOENT)
			{
				_errputs(av[0]);
				_errputs(": 0: Unable to open ");
				_errputs(av[1]);
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
	hsh(data, av);
	return (EXIT_SUCCESS);
}
