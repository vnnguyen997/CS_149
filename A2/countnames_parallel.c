#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_NAMES 100
#define MAX_NAMES_LENGTH 30

int main(int argc, char *argv[]) {

    // check if input arguments are correct
    if (argc < 2) {
        fprintf(stderr, "Usage: countnames <filename> [<filename> ...]\n");
        return 1;
    }

    // Initialize arrays for names and duplicate counts
    char lines[MAX_NAMES][MAX_NAMES_LENGTH];
    int counts[MAX_NAMES] = {0};
    int num_names = 0;

    // Fork for each file and read names from the file
    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();

        if (pid == 0) { // Child process
            // Open the input file
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("Can't open file: %s\n", argv[i]);
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
                    fprintf(stderr,"Warning - Line %d in %s is empty.\n", line_num, argv[i]);
                } else {
                    int found = 0;
                    for (int j = 0; j < num_names; j++) {
                        if (strcmp(line, lines[j]) == 0) {
                            counts[j]++;
                            found = 1;
                            break;
                        }
                    }
                    // if match is not found, then a new name has been found, the new name is added
                    // to the lines array, the number of names is incremented, and the count for that
                    // name is incremented to 1.
                    if (!found) {
                        strncpy(lines[num_names], line, sizeof(lines[num_names]));
                        counts[num_names]++;
                        num_names++;
                    }
                }
                line_num++;
            }
            // Close the file
            fclose(fp);
            // return 0;
        }
        else if (pid < 0) {
            // Error handling for failed fork
            fprintf(stderr, "Failed to fork.\n");
            return 1;
        }
    }

    // Wait for all child processes to complete
    for (int i = 1; i < argc; i++) {
        wait(NULL);
    }

    // Prints the names and their counts
    for (int i = 0; i < num_names; i++) {
        printf("%s: %d\n", lines[i], counts[i]);
    }

    return 0;
}
