/**
 * Description: Program that stores the command lines in an array and
 * traces the memory usage
 * Authors: Vincent Nguyen
 * Author emails: vincent.n.nguyen@sjsu.edu
 * Last modified date: 04-09-2023
 * Creation date: 04-09-2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_COMMANDS 100
#define MAX_COMMANDS_LENGTH 30

int main(void)
{
    pid_t pid;
    int status;
    int i = 0;
    int command_count = 0;

    // create output and error files for this child process
    char out_file[20], err_file[20];

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
        command_count++;

        if ((pid = fork()) < 0) {
            printf("fork error");
        } else if (pid == 0) {        /* child */

            // create files for each child
            sprintf(out_file, "%d.out", getpid());
            sprintf(err_file, "%d.err", getpid());
            int out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
            int err_fd = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);

            // redirect stdout and stderr to output and error files
            dup2(out_fd, 1);
            dup2(err_fd, 2);

            // print start command
            printf("Starting command %d: child %d pid of parent %d)\n",
                   command_count, getpid(), getppid());
            fflush(stdout);

            //execute commands, assuming only 2 arguments will be taken
            execvp(args[0], args);
            printf("couldn't execute: %s", args[0]);
            exit(127);

            close(out_fd);
            close(err_fd);
        }

    }
    /* parent */
    while ((wait ( NULL) != -1) ) {
        // create files for each child
        sprintf(out_file, "%d.out", getpid());
        sprintf(err_file, "%d.err", getpid());
        int out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
        int err_fd = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);

        printf("Finished child %d pid of parent %d", getpid(), getppid());
        if (WIFEXITED(status)) {
            // redirect stdout and stderr to output and error files
            dup2(out_fd, 1);
            fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            dup2(err_fd, 2);
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
        }
        close(out_fd);
        close(err_fd);
    }


    exit(0);
}
