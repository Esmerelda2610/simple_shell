#ifndef SHLL_H
#define SHLL_H

#define _DEFAULT_SOURCE 1

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
#include <signal.h>

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

#define CONVERT_LCASE 1
#define CONVERT_UNSGNED 2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define FILE_HSTR ".simple_shell_history"
#define MAX_HSTR 4096

extern char **environ;

/**
 * struct list_str - a singly linked list
 * @nxt: a pointer to the next node
 * @str: the string
 * @dig: an integer
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
 * @rd_fd: the line input from which fd is read
 * @hist_ct: the number of history line count
 * @cmdbuff_type: the command type buffer
 * @cmdbuff: the command buffer
 */
typedef struct shll_data
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_ct;
	int err_dig;
	int line_ctflags;
	char **environ;
	list_t *alias;
	list_t *hist;
	list_t *envir;
	char *pname;
	int envir_chngd;
	int status;

	char **cmdbuff;
	int cmdbuff_type;
	int rd_fd;
	int hist_ct;
} data_t;

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0} \

/**
 * struct shll_builtin - builtin strings with functions
 * @funct: the function for the builtin
 * @type: the command flag builtin
 */
typedef struct shll_builtin
{
	char *type;
	int (*funct)(data_t *);
} tab_shllbuiltin;

/*ssh loop*/
int hsh(data_t *data, char **argvc);
int bltin_seek(data_t *data);
void cmnd_seek(data_t *data);
void cmd_frk(data_t *data);

/*parse strings*/
int idf_cmnd(data_t *data, char *path);
char *chardup(char *ptstr, int bgn, int end);
char *path_seek(data_t *data, char *ptstr, char *cmnd);

int main(int arc, char **arv);
int loophsh(char **args);

/*error functions*/
void _errputs(char *s);
int errputchar(char c);
int _sputs_fd(char c, int fd);
int _putstrfd(char *s, int fd);

/*shell strings*/
int _sstrlen(char *d);
int _sstrcmp(char *str1, char *str2);
char *pre_substr(const char *str, const char *sub_str);
char *_sstrcat(char *des, char *src);
char *_sstrcpy(char *des, char *sce);

/*shell strings 1*/
char *_sstrdup(const char *s);
void _sputs(char *s);
int _sputchar(char c);
char *_sstrncpy(char *des, char *src, int n);
char *_sstrncat(char *dst, char *sce, int n);

/*string tokenizers*/
char *_sstrchr(char *s, char c);
char **split_str(char *spt, char *dstr);
char **split_delimstr(char *spt, char dstr);

/*shell memory*/
char *set_mem(char *p, char t, unsigned int m);
void free_str(char **strs);
void *shll_realloc(void *p, unsigned int old, unsigned int new);
int free_ptr(void **p);

/*handle strings*/
int interactive(data_t *data);
int is_delim(char c, char *delim);
int is_alphab(int c);
int str_to_int(char *s);

/*handle args*/
int atoi_errs(char *strn);
void err_print(data_t *data, char *strerr);
int deci_print(int feed, int fd);
char *digit_convrt(long int digi, int nbase, int flgs);
void detach_comments(char *bff);

/*shell builtins*/
int shll_exit(data_t *data);
int shll_cd(data_t *data);
int shll_hlp(data_t *data);
int shll_hist(data_t *data);

/*aliases*/
int rmv_alias(data_t *data, char *s);
int aliaset(data_t *data, char *s);
int alias_prnt(list_t *node);
int shll_alias(data_t *data);

/*shell getline*/
ssize_t buffeed(data_t *data, char **bff, size_t *length);
ssize_t get_feed(data_t *data);
ssize_t bufread(data_t *data, char *bff, size_t *j);
int shll_getline(data_t *data, char **p, size_t *len);
void handle_sigint(__attribute__((unused)) int sig_digi);

/*handle input*/
void clear_feed(data_t *data);
void set_feed(data_t *data, char **argvc);
void free_feed(data_t *data, int fields);

/*set unset env*/
int shll_env(data_t *data);
char *shll_getenv(data_t *data, const char *nm);
int shll_setenv(data_t *data);
int shllunset_env(data_t *data);
int envlist_populate(data_t *data);

/*print env*/
char **shget_env(data_t *data);
int shunset_env(data_t *data, char *v);
int shset_env(data_t *data, char *v, char *val);

/*shell hist*/
char *hstfile_ftch(data_t *data);
int hist_wr(data_t *data);
int hist_rd(data_t *data);
int histlist_build(data_t *data, char *bf, int cnt_line);
int hist_recall(data_t *data);

/*linked lists*/
list_t *adnode(list_t **h, const char *s, int digi);
list_t *adnode_atend(list_t **h, const char *s, int digi);
size_t listprnt_str(const list_t *h);
int delnode_atindx(list_t **h, unsigned int inx);
void freelnkd_list(list_t **h_p);

/*linked lists 1*/
size_t lenof_list(const list_t *head);
char **convlist_2str(list_t *hd);
size_t list_prnt(const list_t *head);
list_t *initial_node(list_t *nd, char *prx, char t);
ssize_t getnode_indx(list_t *h, list_t *nd);

/*handle vars*/
int chain_delim(data_t *data, char *bff, size_t *pd);
void chk_chain(data_t *data, char *bff, size_t *b, size_t j, size_t length);
int chng_alias(data_t *data);
int intchnge_vars(data_t *data);
int intchnge_str(char **old_str, char *new_str);

#endif /*SHLL_H*/
