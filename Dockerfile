FROM ubuntu:latest

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
RUN gcc -O3 -I. -o run lib/*.c main.c -lgmp -lpthread

CMD ./run
