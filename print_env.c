#include "shell.h"

void print_env()
{
	for (char **env = environ; *env != 0; env++)
	{
		char *thisEnv = *env;
		printf("%s\n", thisEnv);
	}
}
