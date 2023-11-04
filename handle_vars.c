#include "shell.h"

/**
 * replace_variables - replaces command variables
 * @command: the input command
 * Return: nothing
*/
void replace_variables(char *command)
{
	char new_command[MAX_COMMAND] = "";
	char *start = command;
	char *end;

	while ((end = strchr(start, '$')) != NULL)
	{
		strncat(new_command, start, end - start);

		if (*(end + 1) == '?')
		{
			char exit_status[10];
			sprintf(exit_status, "%d", EXIT_SUCCESS); // Replace with actual exit status
			strcat(new_command, exit_status);
			start = end + 2;
		}
		else if (*(end + 1) == '$')
		{
			char pid[10];
			sprintf(pid, "%d", getpid());
			strcat(new_command, pid);
			start = end + 2;
		}
		else
		{
			strcat(new_command, "$");
			start = end + 1;
		}
	}

	strcat(new_command, start);
	strcpy(command, new_command);
}

/**
 * detach_comments - replaces the first instance of # with \0
 * @bff: the address of string to modify
 * Return: 0 always
*/
void detach_comments(char *bff)
{
	int j;

	for (j = 0; bff[j] != '\0'; j++)
		if (bff[j] == '#' && (!j || bff[j -1] == ' '))
		{
			bff[j] = '\0';
			break;
		}
}

int chain_delim(data_t *data, char *bff, size_t *pd)
{
	size_t k = *pd;

	if (bff[k] == '|' && bff[k + 1] == '|')
	{
		bff[k] = 0;
		k++;
		data->cmdbuff_type = CMMND_OR;
	}
	else if (bff[k] == '&' && bff[k + 1] == '&')
	{
		bff[k] = 0;
		k++;
		data->cmdbuff_type = CMMND_AND;
	}
	else if (bff[k] == ';')
	{
		bff[k] = 0;
		data->cmdbuff_type = CMMND_CHAIN;
	}
	else
		return (0);
	*pd = k;
	return (1);
}
