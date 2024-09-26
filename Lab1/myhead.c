#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void readFromStdin(int nLines) {
    for(int i = 0; i < nLines; i++) {
        char buffer[100];
        scanf("%s", buffer);
        printf("%s\n", buffer);
    }
}

void readFromFile(char *filename, int nLines) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
    } else {
        printf("Reading from file %s\n", filename);
        char buffer[100];
        for (int i = 0; i < nLines && fgets(buffer, 100, file) != NULL; i++) {
            printf("%s", buffer);
        }
        fclose(file);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        readFromStdin(10);
    } else if (argc == 2) {
        if (strstr(argv[1], "-") != NULL) {
            int nLines = atoi(argv[1]) * -1;
            printf("%d", nLines);
            readFromStdin(nLines);
        } else {
            readFromFile(argv[1], 10);
        }
    } else if (argc == 3) {
        if (strstr(argv[1], "-") != NULL) {
            int nLines = atoi(argv[1]) * -1;
            printf("%d", nLines);
            readFromFile(argv[2], nLines);
        } else {
            printf("Invalid arguments\n");
            return 1;
        }
    } else {
        printf("Invalid arguments\n");
        return 1;
    }

    return 0;
}