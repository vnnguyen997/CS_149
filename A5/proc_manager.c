/**
 * Description: Program that executes multiple commands at the same time using fork.
 * Commands are read in through stdin, each command consists of the system call and the argument,
 * each child process creates output files, error files, and executes the commands. The commands
 * are stored in a hash table provided by the professor with slight adjustments. This program
 * measures the amount of time it takes for a process to be start and finished.
 * Authors: Vincent Nguyen
 * Author emails: vincent.n.nguyen@sjsu.edu
 * Last modified date: 04-26-2023
 * Creation date: 04-24-2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>


struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    /* char *name; /* defined name, can remove */
    /* char *defn; /* replacement text, can remove */
    struct timespec starttime, finishtime;
    int index; // this is the line index in the input text file */
    int pid ;  // the process id. you can use the pid result of wait to lookup in the hashtable */
    char *command; // command. This is good to store for when you decide to restart a command */
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* This is the hash function: form hash value for string s */
/* change to: unsigned hash(int pid) */
/* modify to hash by pid . /*
/* You can use a simple hash function: pid % HASHSIZE */
unsigned hash(int pid)
{
    return pid % HASHSIZE;
}

/* lookup: look for s in hashtab */
/* change to lookup by pid: struct nlist *lookup(int pid) */
/* modify to search by pid, you won't need strcmp anymore */
/* This is traversing the linked list under a slot of the hash table. The array position to look in is returned by the hash function */
/* lookup: look for entry with given pid in hashtab */
struct nlist *lookup(int pid)
{
    struct nlist *np;
    for (np = hashtab[hash(pid)]; np != NULL; np = np->next)
        if (pid == np->pid)
            return np; /* found */
    return NULL; /* not found */
}


char *my_strdup(char *);


/* insert: put (name, defn) in hashtab */
/* change this to insert in hash table the info for a new pid and its command */
/* change signature to: struct nlist *insert(char *command, int pid, int index). */
/* This insert returns a nlist node. Thus when you call insert in your main function  */
/* you will save the returned nlist node in a variable (mynode). */
/* Then you can set the starttime and finishtime from your main function: */
/* mynode->starttime = starttime; mynode->finishtime = finishtime; */
struct nlist *insert(char *command, int pid, int index)
{
    struct nlist *np;
    unsigned hashval;

    // change lookup to search by pid
    if ((np = lookup(pid)) == NULL) { /* case 1: the pid is not found, so you have to create it with malloc. Then you want to set the pid, command and index */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->command = my_strdup(command)) == NULL)
            return NULL;
        np->pid = pid;
        hashval = hash(pid);
        np->index = index;
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else { /* case 2: the pid is already there in the hashslot, i.e. lookup found the pid. In this case you can either do nothing, or you may want to set again the command and index (depends on your implementation). */
        // update the command and index
        free(np->command); // free the old command
        np->command = my_strdup(command);
        np->index = index;

    }
    return np;
}

/** You might need to duplicate the command string to ensure you don't overwrite the previous command each time a new line is read from the input file.
Or you might not need to duplicate it. It depends on your implementation. **/
char *my_strdup(char *s) /* make a duplicate of s */
{
    char *p;
    p = (char *) malloc(strlen(s)+1); /* +1 for ’\0’ */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

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
            printf("(Child) Starting command %d: child %d pid of parent %d)\n",
                   command_count, getpid(), getppid());
            fflush(stdout);

            //execute commands, assuming only 2 arguments will be taken
            execvp(args[0], args);
            printf("couldn't execute: %s", args[0]);
            exit(127);

            close(out_fd);
            close(err_fd);
        } else if (pid > 0){ /* parent */
            // add the command, pid, and index to nlist hashtable
            struct nlist *nlist_command = insert(commands[i], pid, i);

            //set the start time
            clock_gettime(CLOCK_MONOTONIC, &nlist_command->starttime);

            // create files for parent
            sprintf(out_file, "%d.out", getpid());
            sprintf(err_file, "%d.err", getpid());
            int out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
            int err_fd = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);

            // redirect stdout and stderr to output and error files
            dup2(out_fd, 1);
            dup2(err_fd, 2);

            // print start command using nlist_command index, pid, and getpid since we're inside parent
            printf("(Parent) Starting command %d: child %d pid of parent %d)\n",
                   nlist_command->index, nlist_command->pid, getpid());
            fflush(stdout);
        }
    }

    /* parent */
    while ((pid = wait ( &status)) > 0) {
        // create files for each child
        sprintf(out_file, "%d.out", getpid());
        sprintf(err_file, "%d.err", getpid());
        int out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
        int err_fd = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);

        // Finished child process
        printf("Finished child %d pid of parent %d", getpid(), getppid());
        fflush(stdout);

        // look up the command node
        struct nlist *get_command = lookup(pid);

        // set the finish time of the command
        clock_gettime(CLOCK_MONOTONIC, &get_command->finishtime);

        // Get elapsed time to finish command
        double elapsed = (get_command->finishtime.tv_sec - get_command->starttime.tv_sec);

        // Print the finished time and elapsed time
        printf("Finished at %ld, runtime duration %f\n", get_command->finishtime.tv_sec, elapsed);

        if (WIFEXITED(status)) {
            // redirect stdout and stderr to output and error files
            dup2(out_fd, 1);
            fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
            if (elapsed <= 2){
                fprintf(stderr, "spawning too fast\n");
            }
        } else if (WIFSIGNALED(status)) {
            dup2(err_fd, 2);
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
            if (elapsed <= 2){
                fprintf(stderr, "spawning too fast\n");
            }
        }

        // if the elapsed duration for the restart
        if (elapsed > 2) {
            // copy command
            char *command_dup = my_strdup(get_command->command);

            // set index
            i = get_command->index;

            // fork child process
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
                printf("(Child) Starting command %d: child %d pid of parent %d)\n",
                       i, getpid(), getppid());
                fflush(stdout);

                // create array for argument tokens
                char *args[20];

                // create tokens from copied command that needed to be restarted
                char *token = strtok(command_dup, " \n");

                // j keeps track of arguments in copied command
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


                // execute commands
                execvp(args[0], args);
                printf("couldn't execute: %s", args[0]);
                exit(127);

                close(out_fd);
                close(err_fd);
            } else if (pid > 0) { /* parent */
                // add the command, pid, and index to nlist hashtable
                struct nlist *nlist_command = insert(commands[i], pid, i);

                //set the start time
                clock_gettime(CLOCK_MONOTONIC, &nlist_command->starttime);

                // create files for parent
                sprintf(out_file, "%d.out", getpid());
                sprintf(err_file, "%d.err", getpid());
                int out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
                int err_fd = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);

                // redirect stdout and stderr to output and error files
                dup2(out_fd, 1);
                dup2(err_fd, 2);

                printf("RESTARTING\n");

                // print start command using nlist_command index, pid, and getpid since we're inside parent
                printf("(Parent) Starting command %d: child %d pid of parent %d)\n",
                       nlist_command->index, nlist_command->pid, getpid());
                fflush(stdout);
            }
        }

        close(out_fd);
        close(err_fd);
    }


    return 0;
}