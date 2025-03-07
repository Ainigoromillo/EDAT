#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "vertex.h"

int main(int argc, char *argv[])
{
    Graph *g = graph_init();
    if (!g)
    {
        printf("Error en graph_init");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        printf("Error en fopen");
        graph_free(g);
        return 1;
    }
    graph_readFromFile(f, g);
    graph_print(stdout, g);
    fclose(f);
    graph_free(g);
    return 0;
}