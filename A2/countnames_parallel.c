#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define MAX_NAMES 100
#define MAX_NAMES_LENGTH 30

int readFile(char *fileName, char lines[MAX_NAMES][MAX_NAMES_LENGTH], int counts[MAX_NAMES]) {
    // Open the input file
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Can't open file %s\n", fileName);
        return 1;
    }

    // Read names from the file and after each loop iteration of the while
    // line number is incremented.
    char line[MAX_NAMES_LENGTH];
    int line_num = 1;
    while (fgets(line, sizeof(line), fp)) {

        // Remove newline character at the end of line
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        // Checking for an empty line otherwise it compares new names to each
        // of the names in the stored array, if a match is found, count is incremented
        if (strlen(line) == 0) {
            fprintf(stderr,"Warning - Line %d in file %s is empty.\n", line_num, fileName);
        } else {
            int found = 0;
            for (int i = 0; i < MAX_NAMES; i++) {
                if (strcmp(line, lines[i]) == 0) {
                    counts[i]++;
                    found = 1;
                    break;
                }
            }
            // if match is not found, then a new name has been found, the new name is added
            // to the lines array, the number of names is incremented, and the count for that
            // name is incremented to 1.
            if (!found) {
                for (int i = 0; i < MAX_NAMES; i++) {
                    if (strlen(lines[i]) == 0) {
                        strncpy(lines[i], line, MAX_NAMES_LENGTH);
                        counts[i]++;
                        break;
                    }
                }
            }
        }
        line_num++;
    }
    // Close the file
    fclose(fp);

    return 0;
}



int main(int argc, char *argv[]) {
    char lines[MAX_NAMES][MAX_NAMES_LENGTH];
    int counts[MAX_NAMES];
    int num_files = argc - 1;
    int ret = 0;

    // Check for the correct number of command-line arguments
    if (num_files < 1) {
        fprintf(stderr, "Usage: countnames_parallel <filename> [<filename> ...]\n");
        return 1;
    }

    // Initialize the lines and counts arrays
    for (int i = 0; i < MAX_NAMES; i++) {
        lines[i][0] = '\0';
        counts[i] = 0;
    }

    // Read each input file by forking a child for each file.
    for (int i = 1; i <= num_files; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Error forking process\n");
            return 1;
        } else if (pid == 0) {
            char *filename = argv[i];
            int ret = readFile(filename, lines, counts);
            if (ret != 0) {
                fprintf(stderr, "Error processing file %s\n", filename);
            }
            exit(0);
        }
    }

    /*
    // Read each input file
    for (int i = 1; i <= num_files; i++) {
        char *filename = argv[i];
        ret = readFile(filename, lines, counts);
        if (ret != 0) {
            fprintf(stderr, "Error processing file %s\n", filename);
            break;
        }
    }
    */

    // Prints the names and their counts
    for (int i = 0; i < MAX_NAMES; i++) {
        if (strlen(lines[i]) > 0) {
            printf("%s: %d\n", lines[i], counts[i]);
        }
    }

    return 0;
}
