C = gcc
CFLAGS = -g -w -std=c99

all: catalan daynumber

catalan: catalan.o
	$(CC) $< -o $@

daynumber: daynumber.o
	$(CC) $< -o $@

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf catalan daynumber *.o *.swp *~
