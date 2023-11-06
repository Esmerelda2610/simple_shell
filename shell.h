#ifndef SHLL_H
#define SHLL_H

/*Authors Joshua Mutuse and Elizabeth Motsinone*/

/*handle arguments*/
#define MAX_LINE 80
#define DELIMITERS " \t\r\n\a"

/*buffers*/
#define BUFFER_SIZE 1024
#define RD_BUFF_SIZE 1024
#define WRT_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/*aliases*/
#define MAX_ALIAS 100

/*variables*/
#define MAX_COMMAND 1024
#define CMMND_NORM 0
#define CMMND_OR 1
#define CMMND_AND 2
#define CMMND_CHAIN 3

#define DATA_INIT \
{NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, \
NULL, 0, 0, 0}

#define CONVERT_LCASE 1
#define CONVERT_UNSGNED 2
#define APLY_GETLINE 0
#define APLY_STRTOK 0
#define FILE_HSTR
#define MAX_HSTR 4096

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>

extern char **environ;

/**
 * struct shll_builtin - builtin strings with functions
 * @funct: the function for the builtin
 * @type: the command flag builtin
*/
typedef struct shll_builtin
{
	int (*funct)(data_t *);
	char *type;
} tab_shllbuiltin;

/**
 * struct list_str - a singly linked list
 * @nxt: a pointer to the next node
 * @str: the string
*/
typedef struct list_str
{
	char *str;
	int dig;
	struct list_str *nxt;
} list_t;

/**
 * struct shll_data - passes pseudoarguments into a function
 *     for uniform function pointer struct prototype
 * @argv: an array of string elements
 * @arg: a string from getline arguments
 * @argc: the number of arguments
 * @path: the current command's string path
 * @status: the last executed command's status
 * @line_ct: the number of errors
 * @envir_chngd: if environment is changed turns on
 * @err_dig: the exit error code
 * @environ: a custom copy modified from LL env
 * @line_ctflags: count this line of input if on
 * @alias: the node for alias
 * @pname: the filename for the program
 * @hist: the node for history
 * @envir: local copy of environ linked list
 * @read_fd: the line input from which fd is read
 * @hist_ct: the number of history line count
 */
typedef struct shll_data
{
	char **argv;
	char *arg;
	int argc;
	char *path;
	int status;
	unsigned int line_ct;
	int envir_chngd;
	int err_dig;
	char **environ;
	int line_ctflags;
	list_t alias;
	char *pname;
	list_t *hist;
	list_t *envir;

	int rd_fd;
	int hist_ct;
	int cmdbuff_type;
	char **cmdbuff;
} data_t;

char **split(char *line);
void shell_loop(void);
int main(int argc, char **argv);
char **split_line(char *line, char *delimiters);
int command_exists(char *command);
ssize_t get_line(char **lineptr, size_t *n, int fd);
void exit_shell(char *command);
void exit();
void set_env_var(char *variable, char *value);
void unset_env_var(char *variable);
void cd_command(char *path);
void execute_command(char *command);
void handle_commands(char *commands);
int execute_comm(char *command);
void handle_logical_operators(char *commands);
int main(int argc, char *argv[]);
void print_env();
size_t rdbuff(data_t *data, char *buff, size_t *j);

/*aliases*/
int hash(char *str);
void insert_alias(char *name, char *value);
int alias_prnt(list_t *node);
void handle_alias_command(char *command);
int aliaset(data_t *data, char *s);
int rmv_alias(data_t *data, char *s);
int shll_alias(data_t *data);

/*variables*/
void replace_variables(char *command);
int chain_delim(data_t *data, char *bff, size_t *pd);
int hsh(data_t *data, char **argvc);
char **shllget_env(data_t *data);
void cmd_frk(data_t *data);
int intchnge_vars(data_t *data);
int intchnge_str(char **old_str, char *new_str);
char *set_mem(char *p, char t, unsigned int m);
void shll_realloc(void *p, unsigned int old, unsigned int new);
void free_str(char **strs);
int free_ptr(void **p);

/*comments*/
void handle_comments(char *command);
int deci_print(int feed, int fd);
void detach_comments(char *bff);
int interactive(data_t *data);
int is_delim(char c, char *delim);
int is_alphab(char c);

/*functions*/
int _sstrlen(char *d);
char *_sstrcpy(char *dest, char *src);
char *_sstrcat(char *dest, char *src);
char *pre_substr(const char *str, const char *sub_str);
int _sstrcmp(char *str1, char *str2);
int _sstrlen(char *d);
int _sputchar(char c);
void _sputs(char *str);
char *_sstrdup(const char *str);
char *_sstrchr(char *s, char c);
char *_sstrncpy(char *dest, char *src, int n);
char *_sstrncat(char *dest, char *src, int n);
void _errputs(char *str);
int errputchar(char c);
int _sputs_fd(char c, int fd);
int _putstrfd(char *str, int fd);
void cmnd_seek(data_t *data);
int idf_cmnd(data_t *data, char *path);
char *path_seek(data_t *data, char *ptstr, char *cmnd);
char *chardup(char *ptstr, int bgn, int end);
int atoi_errs(char *str);
void handle_sigint(__attribute__((unused)) int sig_digi);
ssize_t get_feed(data_t *data);
void chk_chain(data_t *data, char *bff, size_t *b, size_t j, size_t length);
int chng_alias(data_t *data);
void set_feed(data_t *data, char **argvc);
void free_feed(data_t *data, int fields);

/*lists*/
size_t listprnt_str(const list_t *h);
list_t *adnode(list_t **h, const char *s, int digi);
int delnode_atindx(list_t **h, unsigned int inx);
void freelnkd_list(list_t **h_p);
ssize_t getnode_indx(list_t *h, list_t *nd);
list_t *initial_node(list_t *nd, char *prx, char t);
size_t list_prnt(const list_t *head);
char **convlist_2str(list_t *hd);
size_t lenof_list(const list_t *head);
list_t *addnode_atend(list_t **h, const char *s, int dig);

/*enviroment functions*/
int shll_env(data_t *data);
char shll_getenv(data_t *data, const char *nm);
int shll_setenv(data_t *data);
int envlist_populate(data_t *data);
int shllunset_env(data_t *data);
void err_print(data_t *data, char *strerr);
char *digit_convrt(long int digi, int nbase, int flgs);
char **split_str(char *spt, char *dstr);
char **split_delimstr(char *spt, char *dstr);
int shll_getline(data_t *data, char **p, size_t *len);
char **shget_env(data_t *data);
int shunset_env(data_t *data, char *v);
int shset_env(data_t *data, char *v, char *val);
int shll_exit(data_t *data);
int bltin_seek(data_t *data);
int shll_cd(data_t *data);
int shll_hlp(data_t *data);
int shll_hist(data_t *data);

#endif /*SHLL_H*/