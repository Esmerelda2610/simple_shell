#include "shell.h"

void handle_commands(char *commands)
{
	char *command;
	char *rest = commands;

	while ((command = strtok_r(rest, ";", &rest)))
	{
		// Execute each command
		execute_command(command);
	}
}

void execute_command(char *command)
{
	// This is a placeholder function where you would add your code to execute the command.
	// For example, you might fork a new process and use exec to run the command.
	pid_t pid = fork(); // Create a child process

	if (pid < 0)
	{ // Error occurred
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if (pid == 0)
	{				       // Child process
		execlp("/bin/ls", "ls", NULL); // Execute the ls command
	}
	else
	{		    // Parent process
		wait(NULL); // Wait for child to complete
		printf("Child Complete");
	}
	printf("Executing command: %s\n", command);
	return 0;

}
