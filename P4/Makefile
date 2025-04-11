include makefile_ext

########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p4_e1
########################################################
OBJECTSP4E1 = p4_e1.o vertex.o bstree.o file_utils.o
########################################################

all: $(EJS) #clear

p4_e1: $(OBJECTSP4E1)
	$(CC) $(CFLAGS) -o p4_e1 $(OBJECTSP4E1)

vertex.o: vertex.c vertex.h types.h bstree.c
	$(CC) $(CFLAGS) -c vertex.c

p4_e1.o: p4_e1.c vertex.h types.h bstree.h 
	$(CC) $(CFLAGS) -c p4_e1.c