CFLAGS= -Wall -Werror

all: cliente

cliente: cliente.c hash.o lista.o
	gcc $^ -o $@

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

clean:
	rm -rf *.o cliente