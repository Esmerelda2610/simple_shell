#include "shell.h"

/**
 * loophsh - loops the prompt
 * @args: a pointer to the argument
 *
 * Return: 0 if success, 1 if fail
*/
int loophsh(char **args)
{
	while (*args != NULL)
	{
		int status = system(*args);

		if (status != 0)
		{
			printf("Error executing command: %s\n", *args);
			return (1);
		}
		args++;
	}
	return (0);
}
