#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // If no arguments are passed, read from stdin
        while (1) {
            char buffer[100];
            scanf("%s", buffer);
            printf("%s\n", buffer);
        }
    } else if (argc == 2 && strcmp(argv[1], "-") != 0) {
        // Read from file
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("Error opening file\n");
            return 1;
        } else {
            printf("Reading from file %s\n", argv[1]);
            char buffer[100];
            while (fgets(buffer, 100, file) != NULL) {
                printf("%s", buffer);
            }
            fclose(file);
        }
    } else {
        if (strcmp(argv[1], "-") == 0 && argc == 3) {
            // Redirect output to file from stdin
            printf("Redirecting output to file %s\n", argv[2]);
            fclose(fopen(argv[2], "w"));        // Clear the file simulating how the cat command works
            char buffer[100];
            while (1) {
                // Read from stdin and concat to file, updating the file every time a new line is read
                scanf("%s", buffer);
                FILE *file = fopen(argv[2], "a");
                fprintf(file, "%s\n", buffer);
                fclose(file);
            }
        } else {
            printf("Invalid arguments\n");
            return 1;
        }
    }

    return 0;
}