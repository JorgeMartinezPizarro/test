#include <gmp.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t sem;

// Medición de tiempo simple
double now() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

// Test de Lucas-Lehmer optimizado
bool isMersennePrime(long p) {
    if (p == 2) return true;

    mpz_t M, s;
    mpz_inits(M, s, NULL);

    // M = 2^p - 1
    mpz_ui_pow_ui(M, 2, p);
    mpz_sub_ui(M, M, 1);

    mpz_set_ui(s, 4);
    for (long i = 0; i < p - 2; ++i) {
        mpz_mul(s, s, s);          // s = s^2
        mpz_sub_ui(s, s, 2);       // s = s - 2
        mpz_fdiv_r(s, s, M);       // s = s mod M
	}

    bool result = (mpz_cmp_ui(s, 0) == 0);

    mpz_clears(M, s, NULL);
    return result;
}

// Función para cada hilo
void* thread_runner(void* arg) {
    long p = *(long*)arg;
    free(arg);

    sem_wait(&sem); // Esperar a que haya espacio disponible

    double t0 = now();
    if (isMersennePrime(p)) {
        double t1 = now();
        printf("✔  2^%ld - 1 is prime! (%.2f s)\n", p, t1 - t0);
    } else {
        double t1 = now();
        printf("✘  2^%ld - 1 is composite. (%.2f s)\n", p, t1 - t0);
    }

    fflush(stdout);
    sem_post(&sem); // Liberar el semáforo
    return NULL;
}

void computeMersenne() {

    // Array de exponentes p para 2^p - 1
    long numbers[] = {2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107, 127,
                  521, 607, 1279, 2203, 2281, 3217, 4253, 4423,
                  9689, 9941, 11213, 19937, 21701, 23209/*, 44497, 86243, 110503, 132049*/};

    int COUNT = sizeof(numbers) / sizeof(numbers[0]);


    printf("Validating first %d mersenne primes\n", COUNT);
    double start = now();

    sem_init(&sem, 0, 20); // inicializar semáforo

    pthread_t threads[COUNT];
    for (int i = 0; i < COUNT; ++i) {
        long* p = malloc(sizeof(long));
        *p = numbers[i];
        pthread_create(&threads[i], NULL, thread_runner, p);
    }

    for (int i = 0; i < COUNT; ++i) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&sem); // destruir semáforo

    double end = now();
    printf("\nAll tests completed in %.2f seconds.\n", end - start);

    return;
}