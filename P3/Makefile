########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p3_e1
########################################################
OBJECTSP3E1 = p3_e1.o vertex.o delivery.o
########################################################

all: $(EJS) #clear

p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1) -L./ -lqueue

p3_e1.o: p3_e1.c delivery.h types.h queue.h vertex.h
	$(CC) $(CFLAGS) -c p3_e1.c

vertex.o: vertex.c vertex.h types.h
	$(CC) $(CFLAGS) -c vertex.c

delivery.o: delivery.c delivery.h types.h queue.h
	$(CC) $(CFLAGS) -c delivery.c

.PHONY: clear clean run runv

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p3_e1"
	./p3_e1 requests.txt
	
runv:
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full ./p3_e1
	