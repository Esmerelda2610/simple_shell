#include "shell.h"

/**
 * split - splits a string
 * @line: the string to be split
 * Return: the tokens of the split string
*/
char **split(char *line) {
    int bufsize = MAX_LINE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIMITERS);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += MAX_LINE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}

/**
 * shell_loop - loops the terminal cursor
 * Return: nothing
*/
void shell_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = malloc(MAX_LINE * sizeof(char));
        fgets(line, MAX_LINE, stdin);
        args = split(line);

        pid_t pid, wpid;
        pid = fork();

        if (pid == 0) {
            // Child process
            if (execvp(args[0], args) == -1) {
                perror("Error");
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // Error forking
            perror("Error");
        } else {
            // Parent process
            do {
                wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }

        free(line);
        free(args);
    } while (1);
}

/**
 * main - entry point
 * @argc: the argument count
 * @argv: the array elements
 * Return: exit success
*/
int main(int argc, char **argv) {
    shell_loop();
    return EXIT_SUCCESS;
}

/**
 * deci_print - the function prints a base 10 decimal
 * @feed: the user input
 * @fd: a file descriptor written to
 * Return: the count of printed numbers
*/
int deci_print(int feed, int fd)
{
    int j, cnt = 0;
    unsigned int _abs_, curr;
    int (*__sputchar)(char) = _sputchar;

    if (fd == STDERR_FILENO)
        __sputchar = errputchar;
    if (feed < 0)
    {
        _abs_ = -feed;
        __sputchar('-');
        cnt++;
    }
    else
        _abs_ = feed;
    curr = _abs_;
    for (j = 1000000000; j > 1; j /= 10)
    {
        if (_abs_ / j)
        {
            __sputchar('0' + curr / j);
            cnt++;
        }
        curr %= j;
    }
    __sputchar('0' + curr);
    cnt++;

    return (cnt);
}

/**
 * digit_convert - an itoa clone that converts numbers
 * @digi: a digit
 * @nbase: the base
 * @flgs: the flags
 * Return: a string
*/
char *digit_convrt(long int digi, int nbase, int flgs)
{
    char *ptr;
    char sgn = 0;
    static char *arr;
    unsigned long n = digi;
    static char buf[50];

    if (!(flgs & CONVERT_UNSGNED) && digi < 0)
    {
        n = -digi;
        sgn = '-';
    }
    arr = flgs & CONVERT_LCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buf[49];
    *ptr = '\0';

    do{
        *--ptr = arr[n % nbase];
        n /= nbase;
    } while (n != 0);

    if (sgn)
        *--ptr = sgn;
    return (ptr);
}
