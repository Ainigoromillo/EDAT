#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "types.h"

int main(int argc, char *argv[])
{
    Graph *graph = NULL;
    char txt_extension[] = ".txt";
    FILE *pf = NULL;
    long idOrigin, idDest;

    if (argc != 4)
    {
        printf("Error con el numero de argumentos: el formato de los argumentos debe ser: "
               "/file executable file.txt IdOrigin IdDest"
               "");
        return 1;
    }

    if ((strcmp(argv[1] + (strlen(argv[1]) - EXTENSION_LENGTH), txt_extension)))
    {
        printf("El formato del file debe ser: "
               "file.txt"
               "");
        return 1;
    }
    pf = fopen(argv[1], "r");
    if (!pf)
    {
        printf("ERROR EN OPEN");
        return 1;
    }
    idOrigin = atol(argv[2]);
    idDest = atol(argv[3]);
    graph = graph_init();
    if (!graph)
    {
        printf("\nERROR CREATING THE GRAPH\n");
        fclose(pf);
        return 1;
    }
    printf("File name: %s\n", argv[1]);

    if (graph_readFromFile(pf, graph) == ERROR)
    {
        printf("\nERROR READING THE GRAPH FROM FILE\n");
        fclose(pf);
        graph_free(graph);
        return 1;
    }
    
    fclose(pf);
    printf("INPUT GRAPH:\n");
    graph_print(stdout, graph);
    printf("--------BFS-------\n");
    printf("From vertex id: %ld\n To vertex id: %ld", idOrigin, idDest);
    printf("\nOUTPUT:\n");
    if (graph_breathSearch(graph, idOrigin, idDest) == ERROR)
    {
        printf("\nERROR IN BFS\n");
    }
    printf("\n\n--------DFS-------\n");
    printf("From vertex id: %ld\n To vertex id: %ld", idOrigin, idDest);
    printf("\nOUTPUT:\n");
    if (graph_depthSearch(graph, idOrigin, idDest) == ERROR)
    {
        printf("\nERROR IN DFS\n");
    }
    graph_free(graph);

    return 0;
}
