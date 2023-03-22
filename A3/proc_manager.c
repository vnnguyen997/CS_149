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

    // set up arrays for reading and holding commands
    char commands[MAX_COMMANDS][MAX_COMMANDS_LENGTH];
    char *args[MAX_COMMANDS_LENGTH];


    if ((pid = fork()) < 0) {
        printf("fork error");
    } else if (pid == 0) {		/* child */
        execvp(args[0], args);
        printf("couldn't execute: %s", args[0]);
        exit(127);
    }

    /* parent */
    if ((pid = waitpid(pid, &status, 0)) < 0)
        printf("waitpid error");
    printf("DONE ");
    exit(0);
}
