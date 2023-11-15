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
	int fd = 2;

	asm("mov %1, %0\n\t"
	    "add $3, %0"
	    : "=r" (fd)
	    : "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
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
		data->rd_fd = fd;
	}
	envlist_populate(data);
	hist_rd(data);
	hsh(data, av);
	return (EXIT_SUCCESS);
}
