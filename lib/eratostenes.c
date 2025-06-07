#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tools.h"


long raiz_cuadrada_entera(long n) {
    if (n < 0) return -1; // raíz cuadrada no definida para negativos

    long izquierda = 0, derecha = n, resultado = 0;

    while (izquierda <= derecha) {
        long medio = izquierda + (derecha - izquierda) / 2;
        if ((long long)medio * medio <= n) {
            resultado = medio;
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    return resultado;
}

// El primer valor del puntero indica la cantidad de elementos
long *sieve(long n) {
    long *lista;
    
    long limit = raiz_cuadrada_entera(n);

    bool *is_prime = malloc(n * sizeof(bool));

    is_prime[0] = false; // n = 1 (or i = 0 in the array) is not prime!
    
    for (int i = 1; i < n; i++) {
        is_prime[i] = true; // start position true, is prime
    }

    printf("Sieving 0%%");
    fflush(stdout);
    for (long i = 1; i < limit; i++) { // we mark every multiple of i as composite, false
        if (is_prime[i]) {
            printf("\rSieving %ld%%", 100 * i / (limit));
            fflush(stdout);
            for (long j = 2 * i + 1; j < n; j = j + i + 1) {
                is_prime[j] = false;
            }
        }
    }

    puts("\rSieving 100%%\n");
    fflush(stdout);
    
    long number_of_primes = 0;
    for (int i = 0; i < n; i++) {
        if (is_prime[i]) {
            number_of_primes++;
        }
    }

    lista = malloc(number_of_primes * sizeof(int));
    int x = 0;
    int k = 1;
    lista[0] = number_of_primes;
    while (x < n) {
        if (is_prime[x]) {
            lista[k] = x+1;
            k++;
        }
        x++;
    }

    printf("There are %ld primes smaller than %ld.\n\n", number_of_primes, n);
    fflush(stdout);

    
    return lista;
}

void computeEratosthenes(long n) {
    
    puts("");
    double n0 = now();
    long* primes = sieve(n);
    
    long COUNT = primes[0];
    
    for (int i = 9; i >= 0; i--) {
        printf("✅ %ld is prime!\n", primes[COUNT - i]);
        fflush(stdout);
    }

    double n1 = now();

    printf("\nIt took %.2fs.\n", n1 - n0);
}