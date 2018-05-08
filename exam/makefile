CC = gcc
CFLAGS = -g -w -std=c99
all: p1

p1: p1.o

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf p1 *.o *.swp *~
 
