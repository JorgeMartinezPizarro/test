#include <gmp.h>
#include <stdbool.h>

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