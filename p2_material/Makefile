########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p2_e1a p2_e1b p2_e2 p2_e3a p2_e3b
########################################################
OBJECTSP2E1A = p2_e1a.o
OBJECTSP2E1B = p2_e1b.o vertex.o
OBJECTSP2E2 = p2_e2.o graph.o vertex.o

OBJECTSP2E3A = p2_e1a.o vertex.o stack.o
OBJECTSP2E3B = p2_e1b.o vertex.o stack.o
########################################################

all: p2_e1a p2_e1b p2_e2 p2_e3a p2_e3b

p2_e1a: $(OBJECTSP2E1A)
	$(CC) $(CFLAGS) -o p2_e1a $(OBJECTSP2E1A) -L./ -lstack

p2_e1a.o: p2_e1a.c stack.h types.h vertex.h
	$(CC) $(CFLAGS) -c p2_e1a.c


p2_e1b: $(OBJECTSP2E1B)
	$(CC) $(CFLAGS) -o p2_e1b $(OBJECTSP2E1B) -L./ -lstack

p2_e1b.o: p2_e1b.c stack.h types.h vertex.h
	$(CC) $(CFLAGS) -c p2_e1b.c

p2_e2: $(OBJECTSP2E2)
	$(CC) $(CFLAGS) -o p2_e2 $(OBJECTSP2E2) -L./ -lstack

p2_e2.o: p2_e2.c graph.h types.h vertex.h
	$(CC) $(CFLAGS) -c p2_e2.c

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c

graph.o: graph.c vertex.h types.h stack.h
	$(CC) $(CFLAGS) -c graph.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

p2_e3a: $(OBJECTSP2E3A)
	$(CC) $(CFLAGS) -o p2_e3a $(OBJECTSP2E3A)

p2_e3a.o: p2_e1a.c stack.h types.h vertex.h
	$(CC) $(CFLAGS) -c p2_e3a.c


p2_e3b: $(OBJECTSP2E3B)
	$(CC) $(CFLAGS) -o p2_e3b $(OBJECTSP2E3B)

p2_e3b.o: p2_e1b.c stack.h types.h vertex.h
	$(CC) $(CFLAGS) -c p2_e3b.c


.PHONY: clean runa runav runb runbv

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>> Running p2_e1a"
	./p2_e1a grades1.txt grades2.txt
	@echo ">>>>>> Running p2_e1b"
	./p2_e1b cities1.txt cities2.txt
	@echo ">>>>>> Running p2_e2"
	./p2_e2 g2.txt 100 700
	@echo ">>>>>> Running p2_e3a"
	./p2_e3a grades1.txt grades2.txt
	@echo ">>>>>> Running p2_e3b"
	./p2_e3b cities1.txt cities2.txt
run1a:
	@echo ">>>>>> Running p2_e1a"
	./p2_e1a grades1.txt grades2.txt

run1b:
	@echo ">>>>>> Running p2_e1b"
	./p2_e1b cities1.txt cities2.txt

run2:
	@echo ">>>>>> Running p2_e2"
	./p2_e2 g2.txt 100 700

run3a:
	@echo ">>>>>> Running p2_e3a"
	./p2_e3a grades1.txt grades2.txt

run3b:
	@echo ">>>>>> Running p2_e3b"
	./p2_e3b cities1.txt cities2.txt

run1av:
	@echo ">>>>>> Running p2_e1a with valgrind"
	valgrind --leak-check=full ./p2_e1a	grades1.txt grades2.txt

run1bv:
	@echo ">>>>>> Running p2_e1b with valgrind"
	valgrind --leak-check=full ./p2_e1b	cities1.txt cities2.txt

run2v:
	@echo ">>>>>> Running p2_e2 with valgrind"
	valgrind --leak-check=full ./p2_e2 g2.txt 100 700


run3av:
	@echo ">>>>>> Running p2_e3a with valgrind"
	valgrind --leak-check=full ./p2_e3a grades1.txt grades2.txt

run3bv:
	@echo ">>>>>> Running p2_e3b with valgrind"
	valgrind --leak-check=full ./p2_e3b cities1.txt cities2.txt
