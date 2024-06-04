# Nome da Biblioteca
BIBLIOTECA = libregisters.so

HEADER = registers.h

SRC = registers.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -O2 -fPIC

CC = gcc

all: $(BIBLIOTECA) main

$(BIBLIOTECA): $(OBJ)
	$(CC) $(CFLAGS) -shared -o $(BIBLIOTECA) $(OBJ)

dynamic: $(BIBLIOTECA) main.c
	$(CC) -o main main.c -L. -lregisters -o main

static:


clean:
	rm -f $(OBJ) $(BIBLIOTECA) main
