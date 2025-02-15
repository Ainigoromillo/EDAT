#include <stdio.h>
#include "graph.h"
#include "vertex.h"

int main(){
    Graph *g = graph_init();
    long *array;
    if(!graph_newVertex(g, "id:111 tag:Madrid state:WHITE")){
        printf("Ha habido un error");
    }
    if(!(graph_newVertex(g, "id:222 tag:Toledo state:WHITE"))){
        printf("Error");
    }
    graph_newEdge(g, 222, 111);
    printf("111 --> 222? :");
    if(graph_connectionExists(g, 111, 222)){
        printf("Yes\n");
    }else{
        printf("No\n");
    }

    printf("222 --> 111? :");
    if(graph_connectionExists(g, 222, 111)){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
    printf("Number of connections from 111: %d\n", graph_getNumberOfConnectionsFromId(g, 111));
    printf("Number of connections from Toledo: %d\n", graph_getNumberOfConnectionsFromTag(g, "Toledo"));
    array=graph_getConnectionsFromTag(g, "Toledo");
    for(int i=0;i<graph_getNumberOfConnectionsFromTag(g, "Toledo"); i++){
        printf("%ld", array[i]);
    }
    graph_print(stdout, g);
    graph_free(g);
}
