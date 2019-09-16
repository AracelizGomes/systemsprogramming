TARGETS=check_date odd_sum 
CC=gcc
CFLAGS=-Wall -g

all : $(TARGETS)

check_date: check_date.c
	$(CC) $(CFLAGS) -o $@ $<

odd_sum: odd_sum.c
	$(CC) $(CFLAGS) -o $@ $<

clean: 
	@rm -f $(TARGETS) a.out *.o
