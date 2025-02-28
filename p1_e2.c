#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "vertex.h"

int main()
{
    Graph *g = graph_init();
    long *array;
    printf("Inserting Madrid...");
    if (!graph_newVertex(g, "id:111 tag:Madrid state:WHITE"))
    {
        printf("result...:0");
    }else{
        printf("result...:1");
    }
    printf("\nInserting Toledo...");
    if (!(graph_newVertex(g, "id:222 tag:Toledo state:WHITE")))
    {
        printf("result...:0");
    }else{
        printf("result...:1");
    }
    printf("\nInserting edge: 222 -> 111");
    if (graph_newEdge(g, 222, 111) == ERROR)
    {
        return ERROR;
    }

    printf("\n111 --> 222? :");
    if (graph_connectionExists(g, 111, 222))
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }

    printf("222 --> 111? :");
    if (graph_connectionExists(g, 222, 111))
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
    printf("Number of connections from 111: %d\n", graph_getNumberOfConnectionsFromId(g, 111));
    printf("Number of connections from Toledo: %d\n", graph_getNumberOfConnectionsFromTag(g, "Toledo"));
    array = graph_getConnectionsFromTag(g, "Toledo");
    if (!array)
    {
        printf("Error en el array");
        graph_free(g);
        return 1;
    }
    printf("Connections from Toledo: ");
    for (int i = 0; i < graph_getNumberOfConnectionsFromTag(g, "Toledo"); i++)
    {
        printf("%ld", array[i]);
    }
    printf("\nGraph:\n");
    graph_print(stdout, g);
    free(array);
    graph_free(g);
    return 0;
}
