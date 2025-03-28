#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "types.h"

int main(int argc, char*argv[]){
    Graph *graph = NULL;
    char txt_extension[] = ".txt", name[MAX_NAME], product_name[MAX_NAME], str[MAX_LINE_TAM];
    FILE *pf = NULL;
    int num, i;
    void *city = NULL;
    long idOrigin, idDest;

    if(argc != 4){
        printf("Error con el numero de argumentos: el formato de los argumentos debe ser: ""/file executable file.txt IdOrigin IdDest""");
        return 1;
    }

    if((strcmp(argv[1] + (strlen(argv[1]) - EXTENSION_LENGTH), txt_extension))){
        printf("El formato del file debe ser: ""file.txt""");
        return 1;
    }
    pf = fopen(argv[1], "r");
    if(!pf){
        return 1;
    }
    idOrigin = atol(argv[2]);
    idDest = atol(argv[3]);
    graph = graph_init();

    if(!graph){
        printf("\nERROR CREATING THE GRAPH\n");
        fclose(pf);
        return 1;
    }
    if(graph_readFromFile(pf, graph) == ERROR){
        printf("\nERROR READING THE GRAPH FROM FILE\n");
        fclose(pf);
        graph_free(graph);
        return 1;
    }

    fclose(pf);
    printf("INPUT GRAPH:\n");
    graph_print(stdout, graph);
    printf("--------BFS-------\n");
    printf("From vertex id: %ld\n To vertex id: %ld", idDest, idOrigin);
    printf("\nOUTPUT:\n");
    if(graph_breathSearch(graph, idDest, idDest) == ERROR){
        printf("\nERROR IN BFS\n");
    }
    graph_free(graph);

    return 0;
}
