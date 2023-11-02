#include "shell.h"

void exit_shell(char *command)
{
	int status;

	// Check if command is "exit"
	if (strncmp(command, "exit", 4) == 0)
	{
		// Try to parse the status code
		if (sscanf(command + 4, "%d", &status) == 1)
		{
			printf("Exiting the shell with status %d.\n", status);
			exit(status);
		}
		else
		{
			printf("Invalid argument to exit: %s\n", command + 4);
		}
	}
	else
	{
		printf("Unknown command: %s\n", command);
	}
}
