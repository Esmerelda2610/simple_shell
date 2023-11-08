#include "shell.h"

/**
 * hstfile_ftch - fetches the history file
 * @data: a struct of parameters
 * Return: history file in an allocated string
 */
char *hstfile_ftch(data_t *data)
{
	char *bf, *d;

	d = shll_getenv(data, "HOME=");
	if (d == NULL)
		return (NULL);
	bf = malloc(sizeof(char) * (_sstrlen(d) + _sstrlen(FILE_HSTR) + 2));
	if (bf == NULL)
		return (NULL);
	bf[0] = 0;
	_sstrcpy(bf, d);
	_sstrcat(bf, "/");
	_sstrcat(bf, FILE_HSTR);
	return (bf);
}

/**
 * hist_wr - function to create file or append to file
 * @data: a struct of parameters
 * Return: -1 on error, 1 on success
*/
int hist_wr(data_t *data)
{
	char *fname = hstfile_ftch(data);
	list_t *nd = NULL;
	ssize_t fdsp;

	if (!fname)
		return (-1);

	fdsp = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fdsp == -1)
		return (-1);
	for (nd = data->hist; nd; nd = nd->nxt)
	{
		_putstrfd(nd->str, fdsp);
		_sputs_fd('\n', fdsp);
	}
	_sputs_fd(BUFF_FLUSH, fdsp);
	close(fdsp);
	return (1);
}

/**
 * hist_rd - function to read history fromfile
 * @data: a struct of parameters
 * Return: 0 on error, history count on success
*/
int hist_rd(data_t *data)
{
	struct stat st;
	ssize_t fdsp, lenrd, flsz = 0;
	int j, fin = 0, line_cnt = 0;
	char *bf = NULL, *fname = hstfile_ftch(data);

	if (fname == NULL)
		return (0);

	fdsp = open(fname, O_RDONLY);
	free(fname);
	if (fdsp == -1)
		return (0);
	if (!fstat(fdsp, &st))
		flsz = st.st_size;
	if (flsz < 2)
		return (0);
	bf = malloc(sizeof(char) * (flsz + 1));
	if (bf == NULL)
		return (0);
	lenrd = read(fdsp, bf, flsz);
	bf[flsz] = 0;
	if (lenrd <= 0)
		return (free(bf), 0);
	close(fdsp);
	for (j = 0; j < flsz; j++)
		if (bf[j] == '\n')
		{
			bf[j] = 0;
			histlist_build(data, bf + fin, line_cnt++);
			fin = j + 1;
		}
	if (fin != j)
		histlist_build(data, bf + fin, line_cnt++);
	free(bf);
	data->hist_ct = line_cnt;
	while (data->hist_ct-- >= MAX_HSTR)
		delnode_atindx(&(data->hist), 0);
	hist_recall(data);
	return (data->hist_ct);
}



/**
 * histlist_build - function to add an entry to a hist linked list
 * @data: a struct of arguments
 * @bf: the buffer
 * @cnt_line: the count of lines
 * Return: 0 always
*/
int histlist_build(data_t *data, char *bf, int cnt_line)
{
	list_t *nd = NULL;

	if (data->hist)
		nd = data->hist;
	adnode_atend(&nd, bf, cnt_line);

	if (data->hist == NULL)
		data->hist = nd;
	return (0);
}

/**
 * hist_recall - after changing it recalls the history
 * @data: a struct of potential arguments
 * Return: the new history count
*/
int hist_recall(data_t *data)
{
	int k = 0;
	list_t *nd = data->hist;

	while (nd)
	{
		nd->dig = k++;
		nd = nd->nxt;
	}
	return (data->hist_ct = k);
}
