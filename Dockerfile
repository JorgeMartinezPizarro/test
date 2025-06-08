FROM ubuntu:24.04

# Instalar dependencias del sistema
RUN apt-get update && \
    apt-get install -y gcc libgmp-dev && \
    rm -rf /var/lib/apt/lists/*

# Crear directorio de trabajo
WORKDIR /app

# Copiar archivos
COPY main.c .
RUN mkdir ./lib
COPY lib/* ./lib/.

# Compilar el código C con GMP
RUN gcc -g -Wall -Wextra -Werror -O3 -I. -o run lib/*.c main.c -lgmp -lpthread -lm

CMD ./run
