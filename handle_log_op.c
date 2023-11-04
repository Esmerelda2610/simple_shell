#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void handle_logical_operators(char *commands)
{
	char *command;
	char *rest = commands;
	int status;

	while ((command = strtok_r(rest, "&&", &rest)))
	{
		char *sub_command;
		char *sub_rest = command;

		while ((sub_command = strtok_r(sub_rest, "||", &sub_rest)))
		{
			// Execute each command
			status = execute_command(sub_command);

			// If command succeeds, stop processing '||' commands
			if (status == 0)
			{
				break;
			}
		}

		// If command fails, stop processing '&&' commands
		if (status != 0)
		{
			break;
		}
	}
}

int execute_comm(char *command)
{
	// This is a placeholder function where you would add your code to execute the command.
	// For example, you might fork a new process and use exec to run the command.
	// This function should return 0 on success and non-zero on failure.
		char command[100];

		while (1)
		{
			printf("Enter command: ");
			fgets(command, 100, stdin);	     // read command
			command[strcspn(command, "\n")] = 0; // remove newline character

			if (strcmp(command, "env") == 0)
			{
				system("printenv"); // print all environment variables
			}
			else if (strcmp(command, "exit") == 0)
			{
				exit(0); // exit the program
			}
			else if (strncmp(command, "setenv", 6) == 0)
			{
				char var[50], value[50];
				sscanf(command, "setenv %s %s", var, value); // parse variable and value
				setenv(var, value, 1);			     // set environment variable
			}
			else if (strncmp(command, "unsetenv", 8) == 0)
			{
				char var[50];
				sscanf(command, "unsetenv %s", var); // parse variable
				unsetenv(var);			     // unset environment variable
			}
			else if (strncmp(command, "cd", 2) == 0)
			{
				char path[50];
				sscanf(command, "cd %s", path); // parse path
				chdir(path);			// change directory
			}
			else if (strcmp(command, "help") == 0)
			{
				printf("Supported commands: env, exit, setenv VAR VALUE, unsetenv VAR, cd PATH, help\n");
			}
			else if (strcmp(command, "ls") == 0)
			{
				system("ls"); // list directory contents
			}
			else
			{
				printf("Unsupported command\n");
			}
		}

	printf("Executing command: %s\n", command);
	return 0; // Assume success for this example
}
