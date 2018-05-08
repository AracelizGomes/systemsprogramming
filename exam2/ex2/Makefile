CLI = 
SRV = server
OBJS = 
CFLAGS = -g 
LFLAGS =

all: $(SRV)

$(CLI): $(CLI).o $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(CLI) $^

$(SRV): $(SRV).o $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(SRV) $^

clean:
	rm -rf *.o $(CLI) $(SRV) *~
