#include <stdio.h>
#include <string.h>

#define MAX_NAMES 100
#define MAX_NAMES_LENGTH 30

int main() {

    // Open the input file
    FILE *fp = fopen("names.txt", "r");
    if (fp == NULL) {
        printf("Can't open file\n");
        return 1;
    }

    // Initialize arrays for names and duplicate counts
    char lines[MAX_NAMES][MAX_NAMES_LENGTH];
    int counts[MAX_NAMES] = {0};
    int num_names = 0;

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
            fprintf(stderr,"Warning - Line %d is empty.\n", line_num);
        } else {
            int found = 0;
            for (int i = 0; i < num_names; i++) {
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
                strncpy(lines[num_names], line, sizeof(lines[num_names]));
                counts[num_names]++;
                num_names++;
            }
        }
        line_num++;
    }
    // Close the file
    fclose(fp);

    // Prints the names and their counts
    for (int i = 0; i < num_names; i++) {
        printf("%s: %d\n", lines[i], counts[i]);
    }

    return 0;
}