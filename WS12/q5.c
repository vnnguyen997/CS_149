/**
 * Description: Simple Program that does a malloc on an array of size 100 called data.
 * Authors: Vincent Nguyen
 * Author emails: vincent.n.nguyen@sjsu.edu
 * Last modified date: 04-24-2023
 * Creation date: 04-24-2023
 *
 *
 * What happens when this program runs?
 * Nothing happens, it just allocates memory size of int and exits without issues.
 *
 * What happens when you run this program using valgrind?
 * Valgrind shows a loss of 400 bytes in 1 block which is the data array of size 100 ints which is 4 bytes each
 * so 400 bytes is correct the amount of lost data.
 *
 * Is the program correct?
 * The program seems to run okay, but since I didn't free the memory it probably isn't correct.
 *
 * ==49042== Memcheck, a memory error detector
 * ==49042== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
 * ==49042== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
 * ==49042== Command: ./q5
 * ==49042==
 * ==49042== Invalid write of size 4
 * ==49042==    at 0x10916D: main (q5.c:11)
 * ==49042==  Address 0x4a961d0 is 0 bytes after a block of size 400 alloc'd
 * ==49042==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
 * ==49042==    by 0x10915E: main (q5.c:8)
 * ==49042==
 * ==49042==
 * ==49042== HEAP SUMMARY:
 * ==49042==     in use at exit: 400 bytes in 1 blocks
 * ==49042==   total heap usage: 1 allocs, 0 frees, 400 bytes allocated
 * ==49042==
 * ==49042== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
 * ==49042==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
 * ==49042==    by 0x10915E: main (q5.c:8)
 * ==49042==
 * ==49042== LEAK SUMMARY:
 * ==49042==    definitely lost: 400 bytes in 1 blocks
 * ==49042==    indirectly lost: 0 bytes in 0 blocks
 * ==49042==      possibly lost: 0 bytes in 0 blocks
 * ==49042==    still reachable: 0 bytes in 0 blocks
 * ==49042==         suppressed: 0 bytes in 0 blocks
 * ==49042==
 * ==49042== For lists of detected and suppressed errors, rerun with: -s
 * ==49042== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
 */


#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data;

    // create array of integers using malloc
    data = (int*) malloc(100 * sizeof(int));

    // set the value to 0
    data[100] = 0;

    return 0;
}