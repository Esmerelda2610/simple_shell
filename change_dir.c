#include "shell.h"

void cd_command(char *path)
{
	char *home;
	char pwd[1024];

	// If no argument is given, change to home directory
	if (path == NULL)
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			printf("Error: HOME environment variable not set.\n");
			return;
		}
		path = home;
	}

	// Handle 'cd -'
	if (strcmp(path, "-") == 0)
	{
		path = getenv("OLDPWD");
		if (path == NULL)
		{
			printf("Error: OLDPWD environment variable not set.\n");
			return;
		}
	}

	// Attempt to change directory
	if (chdir(path) != 0)
	{
		perror("Error");
		return;
	}

	// Update PWD environment variable
	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("Error");
		return;
	}
	setenv("PWD", pwd, 1);

	// Update OLDPWD environment variable
	setenv("OLDPWD", path, 1);
}
