#include "shell.h"

typedef struct alias
{
	char *name;
	char *value;
} alias;

alias *alias_table[MAX_ALIAS];

int hash(char *str)
{
	int sum = 0;
	for (int i = 0; str[i]; i++)
		sum += str[i];
	return sum % MAX_ALIAS;
}

void insert_alias(char *name, char *value)
{
	int index = hash(name);
	alias *new_alias = malloc(sizeof(alias));
	new_alias->name = strdup(name);
	new_alias->value = strdup(value);
	alias_table[index] = new_alias;
}

void print_alias(char *name)
{
	int index = hash(name);
	if (alias_table[index] != NULL)
		printf("%s='%s'\n", alias_table[index]->name, alias_table[index]->value);
}
