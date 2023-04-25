/**
 * Description: Simple Program that does a malloc on an array of size 100 called data, frees them, and prints
 * out an element.
 * Authors: Vincent Nguyen
 * Author emails: vincent.n.nguyen@sjsu.edu
 * Last modified date: 04-24-2023
 * Creation date: 04-24-2023
 *
 *
 * Does the program run?
 * Yes, the program seems to run without any errors, but it is printing garbage values after the free.
 *
 * What happens when you run this program using valgrind?
 * Valgrind seems to show that there are no leaks.
 *
 * ==49262== Memcheck, a memory error detector
==49262== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==49262== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==49262== Command: ./q6
==49262==
==49262== Invalid write of size 4
==49262==    at 0x1091AD: main (q6.c:62)
==49262==  Address 0x4a961d0 is 0 bytes after a block of size 400 alloc'd
==49262==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==49262==    by 0x10919E: main (q6.c:59)
==49262==
==49262== Conditional jump or move depends on uninitialised value(s)
==49262==    at 0x48E1B56: __vfprintf_internal (vfprintf-internal.c:1516)
==49262==    by 0x48CB81E: printf (printf.c:33)
==49262==    by 0x1091D2: main (q6.c:65)
==49262==
==49262== Use of uninitialised value of size 8
==49262==    at 0x48C533B: _itoa_word (_itoa.c:177)
==49262==    by 0x48E0B3D: __vfprintf_internal (vfprintf-internal.c:1516)
==49262==    by 0x48CB81E: printf (printf.c:33)
==49262==    by 0x1091D2: main (q6.c:65)
==49262==
==49262== Conditional jump or move depends on uninitialised value(s)
==49262==    at 0x48C534C: _itoa_word (_itoa.c:177)
==49262==    by 0x48E0B3D: __vfprintf_internal (vfprintf-internal.c:1516)
==49262==    by 0x48CB81E: printf (printf.c:33)
==49262==    by 0x1091D2: main (q6.c:65)
==49262==
==49262== Conditional jump or move depends on uninitialised value(s)
==49262==    at 0x48E1643: __vfprintf_internal (vfprintf-internal.c:1516)
==49262==    by 0x48CB81E: printf (printf.c:33)
==49262==    by 0x1091D2: main (q6.c:65)
==49262==
==49262== Conditional jump or move depends on uninitialised value(s)
==49262==    at 0x48E0C85: __vfprintf_internal (vfprintf-internal.c:1516)
==49262==    by 0x48CB81E: printf (printf.c:33)
==49262==    by 0x1091D2: main (q6.c:65)
==49262==
this is the int 0
==49262== Invalid read of size 4
==49262==    at 0x1091E7: main (q6.c:71)
==49262==  Address 0x4a96044 is 4 bytes inside a block of size 400 free'd
==49262==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==49262==    by 0x1091DE: main (q6.c:68)
==49262==  Block was alloc'd at
==49262==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==49262==    by 0x10919E: main (q6.c:59)
==49262==
this is the int 0
This works==49262==
==49262== HEAP SUMMARY:
==49262==     in use at exit: 0 bytes in 0 blocks
==49262==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==49262==
==49262== All heap blocks were freed -- no leaks are possible
==49262==
==49262== Use --track-origins=yes to see where uninitialised values come from
==49262== For lists of detected and suppressed errors, rerun with: -s
==49262== ERROR SUMMARY: 7 errors from 7 contexts (suppressed: 0 from 0)

 */


#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data;

    FILE *fp;
    fp = fopen("output.txt", "w"); // open file for writing

    if (fp == NULL) { // check if file was opened successfully
        printf("Error opening file.\n");
        return 1;
    }

    // create array of integers using malloc
    data = (int*) malloc(100 * sizeof(int));

    // set the value to 0
    data[100] = 0;

    // print an element before free
    fprintf(fp,"this is the int %d\n", data[1]);

    // free
    free(data);

    // print element after free
    fprintf(fp,"this is the int %d\n", data[1]);
    fprintf(fp,"This works");

    fclose(fp);


    return 0;
}