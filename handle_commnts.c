#include "shell.h"

void handle_comments(char *command)
{
	char *comment_start = strchr(command, '#');
	if (comment_start != NULL)
	{
		*comment_start = '\0';
	}
}
