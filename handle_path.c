#include "shell.h"

char **split_line(char *line, char *delimiters) {
    int bufsize = MAX_LINE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, delimiters);
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

        token = strtok(NULL, delimiters);
    }
    tokens[position] = NULL;
    return tokens;
}

int command_exists(char *command) {
    char *path = getenv("PATH");
    char **dirs = split_line(path, ":");
    int i;

    for (i = 0; dirs[i] != NULL; i++) {
        char filename[MAX_LINE];
        struct stat buffer;
        snprintf(filename, sizeof(filename), "%s/%s", dirs[i], command);
        if (stat(filename, &buffer) == 0) {
            return 1;
        }
    }
    return 0;
}

void shell_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = malloc(MAX_LINE * sizeof(char));
        fgets(line, MAX_LINE, stdin);
        args = split_line(line, DELIMITERS);

        if (command_exists(args[0])) {
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
        } else {
            printf("%s: command not found\n", args[0]);
        }

        free(line);
        free(args);
    } while (1);
}

int main(int argc, char **argv) {
    shell_loop();
    return EXIT_SUCCESS;
}
