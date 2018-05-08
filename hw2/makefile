cc = gcc
CFLAGS = -g -w -std=c99

all: polyHorner superPerm reverseWord poly

polyHorner: polyHorner.o
	$(cc) $< -o $@

superPerm: superPerm.o
	$(cc) $< -o $@

reverseWord: reverseWord.o
	$(cc) $< -o $@

poly: poly.o
	$(cc) $< -o $@

%.o : %.c
	$(cc) -c $< -o $@


clean:
	rm -rf *.o *~ *.swp .*swp *.swo  polyHorner superPerm reverseWord poly

  
