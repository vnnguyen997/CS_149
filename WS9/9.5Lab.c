/**
 * Description: Program that reads in a string of two words separated by a comma.
 * Program separates the string into two separate words to be printed out removing any
 * white space that may have been entered.
 * Authors: Vincent Nguyen
 * Author emails: vincent.n.nguyen@sjsu.edu
 * Last modified date: 03-31-2023
 * Creation date: 03-31-2023
 */


#include <stdio.h>
#include <string.h>

int main(void) {

    char input[100];
    char *commaPtr;
    char firstWord[50];
    char secondWord[50];

    // we will continuously read from stdin until a 'q' is read to quit
    while (1) {

        // prompt the user for a string and read from stdin
        printf("Enter input string:\n");
        fgets(input, 100, stdin);

        // checks for 'q' to quit
        if (strcmp(input, "q\n") == 0 || strcmp(input, "q") == 0) {
            break;
        }

        // strstr looks for the first occurrence of a substring, in this case ',' a comma
        commaPtr = strstr(input, ",");
        if (commaPtr == NULL) {
            printf("Error: No comma in string.\n\n");
            continue;
        }

        // scans the input until a comma is found, the comma indicates the end of the first word
        // and the beginning of the second word
        // %[^,] means to scan all characters that are NOT a ',' to the first word
        // upon reaching a comma stop reading and expect a ',' to be in the string but don't read it
        // then read the rest of the string for second word
        sscanf(input, "%[^,] , %s", firstWord, secondWord);

        // Use strtok to tokenize the string, using the white space as a delimiter,
        // replacing all white space with null characters, then strcpy, copies the token
        // to the variable
        char *wordPtr;
        wordPtr = strtok(firstWord, " ");
        strcpy(firstWord, wordPtr);
        wordPtr = strtok(secondWord, " ");
        strcpy(secondWord, wordPtr);

        // prints
        printf("First word: %s\n", firstWord);
        printf("Second word: %s\n\n", secondWord);

    }

    return 0;
}