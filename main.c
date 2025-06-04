#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include "lib/mersenne.h"

// Array de exponentes p para 2^p - 1
long numbers[] = {2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107, 127,
                  521, 607, 1279, 2203, 2281, 3217, 4253, 4423,
                  9689, 9941, 11213, 19937, 21701, 23209, 44497/*, 86243, 110503, 132049*/};

#define COUNT (sizeof(numbers) / sizeof(numbers[0]))

// Medición de tiempo simple
double now() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}



// Función para cada hilo
void* thread_runner(void* arg) {
    long p = *(long*)arg;
    free(arg);

    double t0 = now();
    if (isMersennePrime(p)) {
        double t1 = now();
        printf("✔  2^%ld - 1 is prime! (%.2f s)\n", p, t1 - t0);
		fflush(stdout);
    } else {
        double t1 = now();
        printf("✘  2^%ld - 1 is composite. (%.2f s)\n", p, t1 - t0);
		fflush(stdout);
    }
    return NULL;
}

int main() {
    double start = now();
    printf("Validating first %d mersenne primes\n", COUNT);
    pthread_t threads[COUNT];
    for (int i = 0; i < COUNT; ++i) {
        long* p = malloc(sizeof(long));
        *p = numbers[i];
        pthread_create(&threads[i], NULL, thread_runner, p);
    }

    for (int i = 0; i < COUNT; ++i) {
        pthread_join(threads[i], NULL);
    }

    double end = now();
    printf("\nAll tests completed in %.2f seconds.\n", end - start);
    return 0;
}
