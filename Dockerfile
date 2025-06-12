# Etapa de build (compilación)
FROM ubuntu:24.04 as builder

RUN apt-get update && \
    apt-get install -y gcc libgmp-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY lib/ lib/
COPY main.c .

# Compilación estática
RUN gcc -static -O3 -Wall -Wextra -Werror -o myapp main.c lib/*.c -lgmp -lpthread -lm

# Etapa final (runtime)
FROM alpine:latest

# Copiamos solo el binario
COPY --from=builder /app/myapp /bin/myapp

# Ejecutamos el binario
ENTRYPOINT ["/bin/myapp"]