#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "vertex.h"
#define EXTENSION_LENGTH 4

int main(int argc, char *argv[])
{
    char txt_extension[] = ".txt";
    long from_id, to_id;
    FILE *f=NULL;
    Graph *g=NULL;

    if(argc < 4){
        fprintf(stdout, "./p2_e2 g2.txt id1 id2");
        return 1;
    }

    if((strcmp(argv[1] + (strlen(argv[1]) - EXTENSION_LENGTH), txt_extension))){
        fprintf(stdout, "./p2_e2 g2.txt id1 id2");
        return 1;
    }

    if((from_id = atoi(argv[2])) == 0){
        fprintf(stdout, "./p2_e2 g2.txt id1 id2");
        return 1;
    }
    
    if((to_id = atoi(argv[3])) == 0){
        fprintf(stdout, "./p2_e2 g2.txt id1 id2");
        return 1;
    }

    g = graph_init();
    if (!g)
    {
        printf("Error en graph_init");
        return 1;
    }
    f = fopen(argv[1], "r");
    if (!f)
    {
        printf("Error en fopen");
        graph_free(g);
        return 1;
    }
    if(!graph_readFromFile(f, g)){
        printf("\nError reading graph from file %s", argv[1]);
    }
    printf("\nInput graph:\n");
    graph_print(stdout, g);
    fclose(f);
    
    printf("\nBFS output:");
    if(!graph_depthSearch(g, from_id, to_id)){
        printf("\nError in DFS\n");
        return 1;
    }

    graph_free(g);
    return 0;
}