
cc = gcc
CFLAGS = -g -w -std=c99

all: p1

p1: p1.o
	$(CC) $< -o $@


%.o : %.c
	$(cc) -c $< -o $@

clean:
	rm -rf *.o *~ *.swp *.swo transpose 
