#include "shell.h"

int main(void)
{
	char command[100];

	while (1)
	{
		printf("$ ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			exit(0);
		}
		if (system(command) == -1)
		{
			printf("Command not found\n");
		}
	}
	return (0);
}
