#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "vertex.h"

int main(int argc,char *argv[]){
    Graph *g = graph_init();
    FILE *f = fopen(argv[1],"r");
    int d = 0;
    /*graph_readFromFile(f,g);*/
    fscanf(f, "%d", &d);
    printf("g->num_vertices : %d",d);
    graph_print(stdout,g);
    fclose(f);
    graph_free(g);
    return 0;
}