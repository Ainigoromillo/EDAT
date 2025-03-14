########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic
EJS = p2_e1a p2_e1b
########################################################
OBJECTSP2E1A = p2_e1a.o vertex.o stack.o
OBJECTSP2E1B = p2_e1b.o vertex.o stack.o
########################################################

all: p2_e1a p2_e1b

p2_e1a: $(OBJECTSP2E1A)
	$(CC) $(CFLAGS) -o p2_e1a $(OBJECTSP2E1A)

p2_e1a.o: p2_e1a.c stack.h types.h vertex.h
	$(CC) $(CFLAGS) -c p2_e1a.c


stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

p2_e1b: $(OBJECTSP2E1B)
	$(CC) $(CFLAGS) -o p2_e1b $(OBJECTSP2E1B)

p2_e1b.o: p2_e1b.c stack.h types.h vertex.h
	$(CC) $(CFLAGS) -c p2_e1b.c

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c


.PHONY: clean runa runav runb runbv

clean:
	rm -rf *.o $(EJS)

runa:
	@echo ">>>>>> Running p2_e1a"
	./p2_e1a grades1.txt grades2.txt

runb:
	@echo ">>>>>> Running p2_e1b"
	./p2_e1b g1.txt g2.txt


runav:
	@echo ">>>>>> Running p2_e1a with valgrind"
	valgrind --leak-check=full ./p2_e1a	grades1.txt grades2.txt

runbv:
	@echo ">>>>>> Running p2_e1b with valgrind"
	valgrind --leak-check=full ./p2_e1b	g1.txt g2.txt