########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic
EJS = p2_e1a p2_e1b
########################################################
OBJECTSP2E1A = p2_e1a.o
OBJECTSP2E1B = p2_e1b.o vertex.o
OBJECTSP2E2 = p2_e2.o graph.o vertex.o
########################################################

all: p2_e2

p2_e1a: $(OBJECTSP2E1A)
	$(CC) $(CFLAGS) -o p2_e1a $(OBJECTSP2E1A) -L./ -lstack

p2_e1a.o: p2_e1a.c stack.h types.h file_utils.h
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

.PHONY: clean runa runav runb runbv

clean:
	rm -rf *.o $(EJS)

runa:
	@echo ">>>>>> Running p2_e1a"
	./p2_e1a grades1.txt grades2.txt

runb:
	@echo ">>>>>> Running p2_e1b"
	./p2_e1b g1.txt g2.txt

run2:
	@echo ">>>>>> Running p2_e2"
	./p2_e2 g2.txt 100 700


runav:
	@echo ">>>>>> Running p2_e1a with valgrind"
	valgrind --leak-check=full ./p2_e1a	grades1.txt grades2.txt

runbv:
	@echo ">>>>>> Running p2_e1b with valgrind"
	valgrind --leak-check=full ./p2_e1b	g1.txt g2.txt