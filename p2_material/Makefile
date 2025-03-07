########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic
EJS = p2_e1a
########################################################
OBJECTSP2E1 = p2_e1a.o vertex.o
########################################################

all: p2_e1a

p2_e1a: $(OBJECTSP2E1)
	$(CC) $(CFLAGS) -o p2_e1a $(OBJECTSP2E1) -L./ -lstack

p2_e1a.o: p2_e1a.c stack.h types.h vertex.h
	$(CC) $(CFLAGS) -c p2_e1a.c

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c



.PHONY: clean run runv

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>> Running p2_e1a"
	./p2_e1a

runv:
	@echo ">>>>>> Running p2_e1a with valgrind"
	valgrind --leak-check=full ./p2_e1a