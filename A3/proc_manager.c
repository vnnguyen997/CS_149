#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include <sys/wait.h>

#define MAX_COMMANDS 100
#define MAX_COMMANDS_LENGTH 30

int main(void)
{
    pid_t pid;
    int status;
    int i = 0;

    // set up arrays for reading and holding commands
    char commands[MAX_COMMANDS][MAX_COMMANDS_LENGTH];
    char *args[MAX_COMMANDS_LENGTH];

    // read commands from stdin
    while (fgets(commands[i], sizeof(commands[i]), stdin) != NULL) {

        // create tokens from commands array separated by space or \n
        char *token = strtok(commands[i], " \n");

        // j keeps track of arguments in command
        int j = 0;

        // while token isn't null, save tokens to args array
        while (token != NULL) {
            args[j] = token;
            j++;
            //sets token pointer to null or to new token
            token = strtok(NULL, " \n");
        }

        // set end of arguments to NULL for execvp
        args[j] = NULL;

        // increment commands pointer for next command
        i++;


        if ((pid = fork()) < 0) {
            printf("fork error");
        } else if (pid == 0) {        /* child */
            execvp(args[0], args);
            printf("couldn't execute: %s", args[0]);
            exit(127);
        }

    }
    /* parent */
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        printf("DONE ");
    }
    if (pid == -1) {
        printf("waitpid error");
    }

    exit(0);
}
