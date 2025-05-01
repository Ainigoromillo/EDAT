
########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p4_e2
########################################################
OBJECTSP4E1 = p4_e1.o vertex.o bstree.o file_utils.o
OBJECTSP4E2 = p4_e2.o bstree.o file_utils.o search_queue.o
########################################################

all: $(EJS) #clear

p4_e1: $(OBJECTSP4E1)
	$(CC) $(CFLAGS) -o p4_e1 $(OBJECTSP4E1)

p4_e2: $(OBJECTSP4E2)
	$(CC) $(CFLAGS) -o p4_e2 $(OBJECTSP4E2)

vertex.o: vertex.c vertex.h types.h bstree.c
	$(CC) $(CFLAGS) -c vertex.c

p4_e1.o: p4_e1.c vertex.h types.h bstree.h 
	$(CC) $(CFLAGS) -c p4_e1.c
	
bstree.o: bstree.c bstree.h
	$(CC) $(CFLAGS) -c bstree.c

search_queue.o: search_queue.c search_queue.h bstree.h  types.h
	$(CC) $(CFLAGS) -c search_queue.c

p4_e2.o: p4_e2.c search_queue.h types.h file_utils.h
	$(CC) $(CFLAGS) -c p4_e2.c

clean: 
	rm -rf *.o $(EJS)

include Makefile_ext