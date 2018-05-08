SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGETS = $(patsubst %.c,%,$(SRCS))
CC = gcc
CFLAGS = -Wall -g

all : $(TARGETS)

ultraclean: clean
	@rm -f $(TARGETS)

clean: 
	@rm -f $(OBJS)
