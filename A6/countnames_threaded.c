/*****************************************
 * Description: Program expands on Assignment 2 for CS149 which takes two files
 * with names in them and counts them in different threads. The counts will be kept
 * in a hashmap and printed at the end with the names.
 * Authors: Vincent Nguyen
 * Author emails: vincent.n.nguyen@sjsu.edu
 * Last modified date: 05-9-2023
 * Creation date: 05-04-2023
 *
 * CS149 SP23
 * Template for assignment 6
 * San Jose State University
 * originally prepared by Bill Andreopoulos
*****************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

//thread mutex lock for access to the log index
//you need to use this mutexlock for mutual exclusion
//when you print log messages from each thread
pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;

//thread mutex lock for critical sections of allocating THREADDATA
//you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;

//thread mutex lock for access to the name counts data structure
//you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;

void* thread_runner(void*);
pthread_t tid1, tid2;

//struct points to the thread that created the object.
//This is useful for you to know which is thread1. Later thread1 will also
//deallocate.
struct THREADDATA_STRUCT
{
    pthread_t creator;

    // added a filename for the file in the thread
    char filename[30];
};
typedef struct THREADDATA_STRUCT THREADDATA;

THREADDATA* p=NULL;

//variable for indexing of messages by the logging function.
int logindex=0;
int *logip = &logindex;

//The name counts.
// You can use any data structure you like, here are 2 proposals: a linked list OR
// an array (up to 100 names).
//The linked list will be faster since you only need to lock one node, while for
// the array you need to lock the whole array.
//You can use a linked list template from A5. You should also consider using a hash
// table, like in A5 (even faster).
struct NAME_STRUCT
{
    char name[30];
    int count;
};
typedef struct NAME_STRUCT THREAD_NAME;

//array of 100 names
THREAD_NAME names_counts[100];

//node with name_info for a linked list
struct NAME_NODE
{
    THREAD_NAME name_count;
    struct NAME_NODE *next;
};

// Reusing the implementation of hash table in A5
// Replacing all the instances of pid use with name
#define HASHSIZE 100
static struct NAME_NODE *hashtab[HASHSIZE]; /* pointer table */

// This is the hash function: form hash value for pid
int hash(char name)
{
    return name % HASHSIZE;
}

// lookup: look for entry with given name in hashtab
struct NAME_NODE *lookup(char* name)
{
    struct NAME_NODE *np;

    // have to pass in the first letter of name since the hash takes in a char value
    for (np = hashtab[hash(name[0])]; np != NULL; np = np->next)

        // check if name is in the hashtable
        if (name == np->name_count.name)
            return np; /* found */
    return NULL; /* not found */
}

char *my_strdup(char *);


struct NAME_NODE *insert(char* name)
{
    struct NAME_NODE *np;

    // Check to see if the name is in the hashtable
    if ((np = lookup(name)) == NULL) {

        // if not then allocate memory for the name
        np = (struct NAME_NODE *) malloc(sizeof(*np));
        if (np == NULL)
            return NULL;

        // set the name count to 1
        np->name_count.count = 1;

        // have to pass in the first letter of name since the hash takes in a char value
        int hashval = hash(name[0]);

        // set next in NAME_NODE to the new NAME_NODE
        np->next = hashtab[hashval];

        // set the head of the linked list to the newly created NAME_NODE
        hashtab[hashval] = np;
    } else {
        // if name is already there then increment the count
        np->name_count.count = np->name_count.count++;
    }
    return np;
}

char *my_strdup(char *s) /* make a duplicate of s */
{
    char *p;
    p = (char *) malloc(strlen(s)+1); /* +1 for ’\0’ */
    if (p != NULL)
        strcpy(p, s);
    return p;
}
/*********************************************************
// function main
*********************************************************/
int main(int argc, char *argv[])
{
//TODO similar interface as A2: give as command-line arguments three filenames of
// numbers (the numbers in the files are newline-separated).
    if (argc != 3) {
        printf("Usage: program <file1> <file2>\n");
        return 1;
    }

    THREADDATA td1, td2;
    strcpy(td1.filename, argv[1]);
    strcpy(td2.filename, argv[2]);

    printf("create first thread");
    pthread_create(&tid1,NULL,thread_runner,argv[1]);

    printf("create second thread");
    pthread_create(&tid2,NULL,thread_runner,argv[2]);

    printf("wait for first thread to exit");
    pthread_join(tid1,NULL);
    printf("first thread exited");

    printf("wait for second thread to exit");
    pthread_join(tid2,NULL);
    printf("second thread exited");
//TODO print out the sum variable with the sum of all the numbers
    exit(0);
}//end main
/**********************************************************************
// function thread_runner runs inside each thread
**********************************************************************/
void* thread_runner(void* x)
{
    pthread_t me;
    me = pthread_self();
    printf("This is thread %ld (p=%p)",me,p);


    pthread_mutex_lock(&tlock2); // critical section starts
    if (p==NULL) {
        p = (THREADDATA*) malloc(sizeof(THREADDATA));
        p->creator=me;
    }
    pthread_mutex_unlock(&tlock2); // critical section ends


    if (p!=NULL && p->creator==me) {
        printf("This is thread %ld and I created THREADDATA %p",me,p);
    } else {
        printf("This is thread %ld and I can access the THREADDATA %p",me,p);
    }
/**
* //TODO implement any thread name counting functionality you need.
* Assign one file per thread. Hint: you can either pass each argv filename as a
thread_runner argument from main.
* Or use the logindex to index argv, since every thread will increment the logindex anyway
* when it opens a file to print a log message (e.g. logindex could also index
argv)....
* //Make sure to use any mutex locks appropriately
*/
// TODO use mutex to make this a start of a critical section
// critical section starts
    if (p!=NULL && p->creator==me) {
        printf("This is thread %ld and I delete THREADDATA",me);
/**
* TODO Free the THREADATA object.
* Freeing should be done by the same thread that created it.
* See how the THREADDATA was created for an example of how this is done.
*/
    } else {
        printf("This is thread %ld and I can access the THREADDATA",me);
    }
// TODO critical section ends
    pthread_exit(NULL);
//return NULL;
}//end thread_runner