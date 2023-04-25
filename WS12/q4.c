/**
 * Description: Simple Program that does a malloc and doesn't free before exiting.
 * Authors: Vincent Nguyen
 * Author emails: vincent.n.nguyen@sjsu.edu
 * Last modified date: 04-24-2023
 * Creation date: 04-24-2023
 *
 *
 * What happens when this program runs?
 * Nothing happens, it just allocates memory size of int and exits
 *
 * Can you use gbd to find any problems with it?
 * I can't find any problems with it using gdb
 *
 * How about valgrind?
 * Yes, with valgrind I am getting definite leaks of 4 bytes which is the size of the int.
 *
 * ==48895== Memcheck, a memory error detector
   ==48895== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
   ==48895== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
   ==48895== Command: ./q4
   ==48895==
   ==48895==
   ==48895== HEAP SUMMARY:
   ==48895==     in use at exit: 4 bytes in 1 blocks
   ==48895==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
   ==48895==
   ==48895== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
   ==48895==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   ==48895==    by 0x10915E: main (q4.c:7)
   ==48895==
   ==48895== LEAK SUMMARY:
   ==48895==    definitely lost: 4 bytes in 1 blocks
   ==48895==    indirectly lost: 0 bytes in 0 blocks
   ==48895==      possibly lost: 0 bytes in 0 blocks
   ==48895==    still reachable: 0 bytes in 0 blocks
   ==48895==         suppressed: 0 bytes in 0 blocks
   ==48895==
   ==48895== For lists of detected and suppressed errors, rerun with: -s
   ==48895== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int* ptr = malloc(sizeof(int));
    return 0;
}