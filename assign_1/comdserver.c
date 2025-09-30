#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

    
    while (1) {
        char *input = calloc(ARG_MAX + 2, sizeof(char));
        char *command = calloc(PATH_MAX + 1, sizeof(char));
        char *token;
        char **args = calloc(4096, sizeof(char*));
        fgets(input, ARG_MAX + 2, stdin); // input = input + \n + \0
        input[strcspn(input, "\n")] = 0; // replace newline with null terminator
        token = strtok(input, " ");
        strcpy(command, token);
        args[0] = calloc(strlen(command) + 1, sizeof(char));
        
        int j = 0;
        for (int i = strlen(command) - 1; i > -1; i--) {
            if (command[i] == '/') {
                j = i + 1;
                break;
            }
        }

        for (int i = j; i < strlen(command) + 1; i++) {
            args[0][i-j] = command[i];
        }

        int i = 1;
        while (1) {
            token = strtok(NULL, " ");
            if (token == NULL) {
                break;
            }
            args[i] = calloc(strlen(token) + 1, sizeof(char));
            strcpy(args[i], token);
            i++;
        }

        for (int i = 0; i < argc; i++) {
            if (strcmp(argv[i], command) == 0) {
                pid_t p = fork();
                if (p == 0) {
                    execv(command, args);
                }
            }
        }

        free(input);
        free(command);
        i = 0;
        while (1) {
            if (args[i] == NULL) {
                break;
            }
            free(args[i]);
            i++;
        }
        free(args);
    }

    return 0;

}