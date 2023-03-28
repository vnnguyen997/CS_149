#include <stdio.h>
#include <string.h>

// Function takes an input string and input character from stdin
int CalcNumCharacters(char* userString, char userChar) {

    int i = 0;
    int count = 0;

    // loops through the input string until it reaches a null character
    // incrementing a counter for the occurrences of the user char in the
    // user string
    while (userString[i] != '\0') {
        if (userString[i] == userChar) {
            count++;
        }
        i++;
    }
    return count;
}

int main(void) {

    char userChar;
    char userString[50];

    // scan in a character and string
    scanf("%c %s", &userChar, userString);

    // pass the input char and string to CalcNumCharacters function
    int occurrences = CalcNumCharacters(userString, userChar);

    // Print the singular case, else the multiple case
    if (occurrences == 1) {
        printf("%d %c \n", occurrences, userChar);
    } else {
        printf("%d %c's \n", occurrences, userChar);
    }

    return 0;
}


