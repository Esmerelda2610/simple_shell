#include "shell.h"

void execute_command(char *command);

int main(int argc, char *argv[])
{
	FILE *file;
	char command[MAX_COMMAND];

	if (argc != 2)
	{
		printf("Usage: %s [filename]\n", argv[0]);
		return 1;
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return 1;
	}

	while (fgets(command, sizeof(command), file) != NULL)
	{
		// Remove trailing newline
		command[strcspn(command, "\n")] = '\0';

		// Execute the command
		execute_command(command);
	}

	fclose(file);

	return 0;
}
