#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
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
long sieve(long n) {
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

    /*lista = malloc(number_of_primes * sizeof(int));
    int x = 0;
    int k = 1;
    lista[0] = number_of_primes;
    while (x < n) {
        if (is_prime[x]) {
            lista[k] = x+1;
            k++;
        }
        x++;
    }*/

    printf("There are %ld primes smaller than %ld.\n\n", number_of_primes, n);
    fflush(stdout);

    
    return number_of_primes;
}

void computeEratosthenes(long n) {
    
    puts("");
    double n0 = now();
    
    sieve(n);
    
    double n1 = now();

    printf("It took %.2fs.\n", n1 - n0);
}


#define MAX_THREADS 10  // Puedes ajustar según tu CPU

typedef unsigned long long ull;

ull total_primes = 0;
pthread_mutex_t lock;

ull N = 0ULL;  // 10 mil millones
ull sqrtN;
ull block_size = 0ULL;  // 10000 bloque

bool* base_primes;  // Primos hasta sqrt(N)
ull base_prime_count = 0;
ull* base_prime_list;

// Estructura para pasar a cada hilo
typedef struct {
    ull low;
    ull high;
    int thread_id;
} Task;

void sieve_base() {
    sqrtN = (ull)sqrt(N) + 1;
    base_primes = calloc(sqrtN + 1, sizeof(bool));
    for (ull i = 2; i <= sqrtN; ++i)
        base_primes[i] = true;

    for (ull i = 2; i * i <= sqrtN; ++i) {
        if (base_primes[i]) {
            for (ull j = i * i; j <= sqrtN; j += i)
                base_primes[j] = false;
        }
    }

    // Guardar los primos encontrados
    for (ull i = 2; i <= sqrtN; ++i) {
        if (base_primes[i]) base_prime_count++;
    }

    base_prime_list = malloc(base_prime_count * sizeof(ull));
    int idx = 0;
    for (ull i = 2; i <= sqrtN; ++i)
        if (base_primes[i])
            base_prime_list[idx++] = i;
    
    total_primes += base_prime_count;
}

// Función que cada hilo ejecuta
void* segment_sieve(void* arg) {
    Task* task = (Task*)arg;
    ull low = task->low;
    ull high = task->high;

    bool* is_prime = calloc(high - low + 1, sizeof(bool));
    for (ull i = 0; i <= high - low; ++i)
        is_prime[i] = true;

    for (ull i = 0; i < base_prime_count; ++i) {
        ull p = base_prime_list[i];
        ull start = (low + p - 1) / p * p;
        if (start < p * p) start = p * p;

        for (ull j = start; j <= high; j += p)
            is_prime[j - low] = false;
    }

    // Cuenta primos encontrados en este segmento
    ull count = 0;
    for (ull i = 0; i <= high - low; ++i)
        if (is_prime[i])
            count++;

    // 🔒 Sección crítica protegida
    pthread_mutex_lock(&lock);
    total_primes += count;
    pthread_mutex_unlock(&lock);
    // 🔓 Fin de la sección crítica

    //printf("Thread %d: [%llu - %llu] tiene %llu primos\n", task->thread_id, low, high, count);

    free(is_prime);
    free(task);
    return NULL;
}


void computeSegmentedEratosthenes() {
    puts("");
    fflush(stdout);
    // 1. Resetear variables globales
    total_primes = 0;
    base_prime_count = 0;
    sqrtN = 0;
    N = 1000000000000ULL; // 1 trillion
    block_size = 100000000ULL;  // 100 million

    // 2. Inicializar mutex
    pthread_mutex_init(&lock, NULL);

    double t0 = now();
    
    printf("Sieving 0%%");
    fflush(stdout);
    sieve_base();

    ull current = sqrtN + 1;
    pthread_t threads[MAX_THREADS];

    int thread_idx = 0;

    while (current <= N) {

        printf("\rSieving %lld%%   ", 100 * current / N);
        fflush(stdout);
        ull next = current + block_size - 1;
        if (next > N) next = N;

        Task* t = malloc(sizeof(Task));
        t->low = current;
        t->high = next;
        t->thread_id = thread_idx;

        pthread_create(&threads[thread_idx], NULL, segment_sieve, t);
        thread_idx++;

        if (thread_idx == MAX_THREADS) {
            for (int i = 0; i < MAX_THREADS; ++i)
                pthread_join(threads[i], NULL);
            thread_idx = 0;
        }

        current = next + 1;
    }

    printf("\rSieving 100%%            ");
    // Últimos hilos
    for (int i = 0; i < thread_idx; ++i)
        pthread_join(threads[i], NULL);


    free(base_primes);
    free(base_prime_list);

    // 5. Destruir mutex (opcional si vas a reusarlo)
    pthread_mutex_destroy(&lock);

    printf("Found %lld primes up to %lld\n", total_primes, N);
    printf("\nIt took %.2fs.\n", now() - t0);
}