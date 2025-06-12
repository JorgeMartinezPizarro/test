#include <stdio.h>
#include "tools.h"

void helloWorld(void) {
    puts("HelloWorld");
}

void usingPointers() {
    char character = 'X';
    char *pointer = &character;
    printf(" 1 - Pointer to a char:\n\n");
    printf("Initial value of the character c: '%c'\n", character);
    printf("We set the pointer to point a char with value '0'\n");
    // We change to value that the pointer is pointing to.
    *pointer = '0';
    printf("The pointer *c points to the position %p (HEX) in the memory\n", (void *)pointer);
    printf("Character of c changed to: '%c'\n", character);
    printf("\n 2 - Pointer to a pointer to a char:\n\n");
    char **pointerToAPointer = &pointer;
    character = 'X';
    printf("Initial value of the character c: '%c'\n", character);
    **pointerToAPointer = '0';
    printf("The pointer of the pointer points to a pointer in the position %p (HEX) in the memory\n", (void *)(void *)pointerToAPointer);
    printf("We set the pointer to a pointer to point to a char with value '0'\n");
    printf("Character c changed to: '%c'\n", character);
}

void runTests(void) {
    double start = now();

    printf("\n [1] - Running 'helloWorld()'\n\n");
    helloWorld();

    printf("\n [2] - Running 'usingPointers()'\n\n");
    usingPointers();

    double end = now();
    double duration = end - start;
    printf("\n2 test finished in %.2f seconds\n", duration);
}