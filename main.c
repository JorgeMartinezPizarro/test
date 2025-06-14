#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "lib/eratostenes.h"
#include "lib/mersenne.h"
#include "lib/strings.h"
#include "lib/integers.h"
#include "lib/basics.h"


int main() {

    char *programs[] = {
        "Say Hello World!",
        "Find Mersenne primes smallers than 10E7000 using LLT", 
        "Count primes smallers than 10E9 with the Eratosthenes sieve",
        "Count primes smallers than 10E9 with the segmented sieve",
        "Split strings by multi-byte characters",
        "Integers and Combinations",
        "Pointers and values",
        "Close and Exit"
    };
    
    int n = sizeof(programs) / sizeof(programs[0]);
    int numero = -1;
    int valido;

    while (numero != n -1) {
        valido = 0;
        numero = -1;
        while (!valido) {
            printf("/////////////////////////////////////////////////////////////////////////////////////////\n");
            printf("        __  __    _    _____ _   _ \n");
            printf("       |  \\/  |  / \\  |_   _| | | |\n");
            printf("       | |\\/| | / _ \\   | | | |_| |\n");
            printf("       | |  | |/ ___ \\  | | |  _  |\n");
            printf("       |_|  |_/_/   \\_\\ |_| |_| |_|\n");
            printf("\n");
            printf("Hi human! What can I do... for ya?\n\n");
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

        printf("\n✅ Selected: %d - %s\n", numero, programs[numero]);
        fflush(stdout);
        
        if (numero == 0) {
            helloWorld();
        } else if (numero == 1) {
            computeMersenne();
        } else if (numero == 2) {
            computeEratosthenes(1000000000);
        } else if (numero == 3) {
            computeSegmentedEratosthenes();
        } else if (numero == 4) {
            exploreStrings();
        } else if (numero == 5) {
            
            for (int n = 1; n <= 10; n++) {
                printf("\n\n - The %d! / (%d! * (%d - %d)!) subsets of the 10-digits set taken %d by a time:\n\n", 10, n, 10, n , n);
                fflush(stdout);
                print_combinations(n);
            }

            puts("  ");
            fflush(stdout);
            
        } else if (numero == 6) {
            runTests();
        } else if (numero == n - 1) {
            puts("\nExiting ...");
        } else {
            puts("\nNothing to do ...");
        }
        
        puts("");
    }
    return 0;
}
