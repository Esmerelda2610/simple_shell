#include "shell.h"

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
