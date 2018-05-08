cc = gcc
all: powerMod fib

powerMod: powerMod.o
	$(cc) $< -o $@

fib: fib.o
	$(cc) $< -o $@

%.o : %.c
	$(cc) -c $< -o $@

clean:
	rm -rf *.o *~ *.swp powerMod fib
