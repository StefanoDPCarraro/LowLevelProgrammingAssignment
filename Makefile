CFLAGS = -Wall -O2

PROG = controller
FONTES = main.c registers.c
OBJETOS = $(FONTES:.c=.o)

all: dynamic

static:
	gcc $(CFLAGS) -c registers.c
	ar rcs libregisters.a registers.o
	gcc $(CFLAGS) main.c -o $(PROG) -L. -lregisters

dynamic:
	gcc $(CFLAGS) -c -fPIC registers.c
	gcc $(CFLAGS) -shared -o libregisters.so registers.o
	gcc $(CFLAGS) main.c -o $(PROG) -L. -lregisters

clean:
	rm -f $(PROG) $(OBJETOS) libregisters.a libregisters.so