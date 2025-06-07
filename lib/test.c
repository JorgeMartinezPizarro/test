#include <stdio.h>
#include "tools.h"

void splitString(char* emojis) {
    // Imprimir string completo
    fputs("Split ", stdout);
    fputs(emojis, stdout);
    puts(" into chars:\n");

    int i = 0;
    int count = 0;
    while (emojis[i] != '\0') {
        unsigned char byte = emojis[i];
        int len = 0;
        int next_len = 0;
        // Detectar longitud del carácter UTF-8
        if ((byte & 0b10000000) == 0) len = 1;
        else if ((byte & 0b11100000) == 0b11000000) len = 2;
        else if ((byte & 0b11110000) == 0b11100000) len = 3;
        else if ((byte & 0b11111000) == 0b11110000) len = 4;
        else len = 1;

        // Caso especial: si emoji actual es 🐱 (4 bytes) y sigue ZWJ + 👤 (3 + 4 bytes)
        if (len == 4
            && (unsigned char)emojis[i] == 0xF0
            && (unsigned char)emojis[i + 1] == 0x9F
            && (unsigned char)emojis[i + 2] == 0x90
            && (unsigned char)emojis[i + 3] == 0xB1) {

            // Verificamos ZWJ (3 bytes)
            if ((unsigned char)emojis[i + 4] == 0xE2
                && (unsigned char)emojis[i + 5] == 0x80
                && (unsigned char)emojis[i + 6] == 0x8D) {

                // Verificamos 👤 (4 bytes)
                if ((unsigned char)emojis[i + 7] == 0xF0
                    && (unsigned char)emojis[i + 8] == 0x9F
                    && (unsigned char)emojis[i + 9] == 0x91
                    && (unsigned char)emojis[i + 10] == 0xA4) {

                    len = 11; // 4 + 3 + 4 bytes juntos
                }
            }
        }

        if (emojis[i + len] == (char)0xEF &&
            emojis[i + len + 1] == (char)0xB8 &&
            emojis[i + len + 2] == (char)0x8F) {
            next_len = 3;
        }

        // Si sí, sumamos esos 3 bytes para imprimirlos juntos
        len = len + next_len;

        fputs("✅ Char nr. ", stdout);
        char es[2];
        itoc(++count, es);
        fputs(es, stdout);
        fputs(" ", stdout);
        for (int j = 0; j < len; j++) {
            putchar((unsigned char)emojis[i + j]);
        }

        fputs(" with length ", stdout);
        char it[2];
        itoc(len, it);
        fputs(it, stdout);
        putchar('\n');
        
        i += len;
    }

    return;
}

void exploreStrings() {
    puts("");

    char* emojis = "😀🎉🌟🔥🚀🍕🎵🐱‍👤🌈🍀🦄🍩🎨🐉🌸⚡️🐢🍎💡🎬🎧🛸🎁🎲🚴";

    splitString(emojis);

    char* jorge = "Martínez";

    putchar('\n');

    splitString(jorge);

    putchar('\n');
    return;
}
