#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib/eratostenes.h"
#include "lib/mersenne.h"
#include "lib/test.h"


int main() {

    char *programs[] = {
        "The Lucas Lehmer Test", 
        "The Eratosthenes Sieve",
        "String and char functions",
        "Exit"
    };
    
    int n = sizeof(programs) / sizeof(programs[0]);
    int numero = -1;
    int valido;

    while (numero != n -1) {
        valido = 0;
        numero = -1;
        while (!valido) {
            printf("//////////////////////////////////////////////////////////////////////////////////////////////\n");
            printf("   __  __    _    _____ _   _ \n");
            printf("  |  \\/  |  / \\  |_   _| | | |\n");
            printf("  | |\\/| | / _ \\   | | | |_| |\n");
            printf("  | |  | |/ ___ \\  | | |  _  |\n");
            printf("  |_|  |_/_/   \\_\\ |_| |_| |_|\n");
            printf("\n");
            printf("Select an option to run: \n\n");
            for (int i = 0; i < n; i++) {
                printf(" %d: %s.\n", i, programs[i]);
            }
            
            printf("\n> ");
            fflush(stdout);
            if (scanf("%d", &numero) != 1) {
                // Limpiar entrada inválida (como letras)
                while (getchar() != '\n'); // Vacía el buffer
                printf("❌ Invalid option! Try again.\n\n");
                fflush(stdout);
                continue;
            }

            if (numero >= 0 && numero < n) {
                valido = 1;
            } else {
                printf("\n❌ Invalid option! Try again.\n\n");
                fflush(stdout);
            }
        }

        printf("\n✅ Selected: %d\n", numero);
        
        if (numero == 0) {
            computeMersenne();
        } else if (numero == 1) {
            computeEratosthenes(100000000);
        } else if (numero == 2) {
            doThings();
        } else if (numero == n - 1) {
            puts("\nExiting ...");
        } else {
            puts("\nNothing to do ...");
        }
        puts("");
    }
    return 0;
}
