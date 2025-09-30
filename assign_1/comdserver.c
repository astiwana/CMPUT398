#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    char *input = calloc(2097153, sizeof(char)); // 2097152 is linux line argument length limit (ARG_MAX)
    char *output = calloc(4096, sizeof(char));
    
    while (1) {

        fgets(input, 8192, stdin); // input = input + \n + \0
        input[strcspn(input, "\n")] = 0; // replace newline with null terminator
       
        int space = 0;
        while (input[space] != ' ' && input[space] != '\0') {
            space++;
        }

        char command[space+1];
        memcpy(command, input, space);
        command[space] = '\0';

        for (int i = 0; i < argc; i++) {
            if (strcmp(argv[i], command) == 0) {
                FILE *fp = popen(input, "r");
                if (!fp) {
                    break;
                }
                while (fgets(output, 4096, fp)) {
                    printf("%s", output);
                }
                pclose(fp);
                break;
            }
        }
    }

    return 0;

}