#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib/mersenne.h"


int main() {

    char *programs[] = {"Compute the first mersenne primes", "Compute the first primes", "Exit"};
    int n = sizeof(programs) / sizeof(programs[0]);
    int numero;
    int valido = 0;

    while (!valido) {
        printf("Select an option to run: \n\n");
        for (int i = 0; i < n; i++) {
            printf(" - %d: %s.\n", i, programs[i]);
        }
        
        printf("\n");
        fflush(stdout);
        if (scanf("%d", &numero) != 1) {
            // Limpiar entrada inválida (como letras)
            while (getchar() != '\n'); // Vacía el buffer
            printf("Wrong option! Try again.\n");
            fflush(stdout);
            continue;
        }

        if (numero >= 0 && numero < n) {
            valido = 1;
        } else {
            printf("\nWrong option! Try again.\n");
            fflush(stdout);
        }
    }

    printf("\nSelected: %d\n", numero);
    
    if (numero == 0) {
        computeMersenne();
    } else if (numero == 1) {
        printf("\nThe first primes are: 2, 3, 5, 7, 11, 13 ...");
    } else if (numero == 2) {
        puts("\nExiting ...");
    } else {
        puts("\nNothing to do ...");
    }
    puts("");
    return 0;
}
