#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define MAX_VTX 4096
struct _Graph {
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};
/**
 * @brief Creates a new empty graph.
 *
 * Allocates memory for a new graph and initializes it to be empty 
 * (no vertices and no edges).
 *
 * @return A pointer to the graph if it was correctly allocated, 
 * NULL otherwise.
 **/
Graph * graph_init(){
    Graph *graph = NULL;
    graph = (Graph *)malloc(sizeof(Graph));
    if(!graph) return NULL;
    return graph;
}

/**
 * @brief Frees a graph.
 *
 * Frees all the memory allocated for the graph.
 *
 * @param g Pointer to graph to be freed.
 **/
void graph_free(Graph *g){
    int i;
    for(i = 0; i < g->num_vertices ; i++){
        if(g->vertices[i]) free(g->vertices[i]);
    }
    free(g);
}

/**
 * @brief Inserts a new vertex in a graph.
 *
 * Creates a vertex by calling vertex_initFromString and adds it to
 * a graph. If a vertex with the same id already exists in the graph, 
 * it is not added. 
 *
 * @param g Pointer to the graph.
 * @param desc Description of the vertex.
 *
 * @return Returns OK if the vertex could be created (or if it exists 
 * already), ERROR otherwise.
 **/
Status graph_newVertex(Graph *g, char *desc){
    if(!g) return ERROR;
    int i,j = 0;
    Vertex *Nvertex = NULL;
    Nvertex = vertex_initFromString(desc);
    for(i = 0; i < g->num_vertices; i++){
        if(vertex_getId(Nvertex) == vertex_getId(g->vertices[i])) j = 1;break;
    }
    if(j == 1){
        return OK;
    }
    g->num_vertices ++;
    g->vertices[g->num_vertices - 1] = Nvertex;
    return OK;
}

/**
 * @brief Creates an edge between to vertices of a graph.
 *
 * If any of the two vertices does not exist in the graph the edge is
 * not created.
 *
 * @param g Pointer to the graph.
 * @param orig ID of the origin vertex.
 * @param dest ID of the destination vertex.
 *
 * @return OK if the edge could be added to the graph, ERROR otherwise.
 **/
Status graph_newEdge(Graph *g, long orig, long dest){
    Bool found=FALSE;
    int i,j;
    if(!graph_contains(g, orig) || !graph_contains(g, dest)){
        return ERROR;
    }
    for(i=0;i<MAX_VTX && !found;i++){
        if(orig == vertex_getId((g->vertices[i]))){
            found=TRUE;
        }
    }
    found=FALSE;
    for(j=0;j<MAX_VTX && !found;j++){
        if(orig == vertex_getId((g->vertices[j]))){
            found=TRUE;
        }
    }
    (g->num_edges)++;
    (g->connections[i][j])++;
    return OK;
}

/**
 * @brief Checks if a graph contains a vertex.
 *
 * @param g Pointer to the graph.
 * @param id ID of the vertex.
 *
 * @return Returns TRUE if there is a vertex in the graph g with the
 * ID id, FALSE otherwise.
 **/
Bool graph_contains(const Graph *g, long id){
    if(!g) return ERROR;
    for(int i=0;i<MAX_VTX;i++){
        if(id == vertex_getId((g->vertices)[i])){
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * @brief Returns the total number of vertices in a graph.
 *
 * @param g Pointer to the graph.
 *
 * @return Returns The number of vertices in the graph, or -1 if 
 * there is any error.
 **/
int graph_getNumberOfVertices(const Graph *g){
    if(!g) return -1;
    return g->num_vertices;
}

/**
 * @brief Returns the total number of edges  * in the graph.
 *
 * @param g Pointer to the graph.
 *
 * @return Returns The number of vertices in the graph, or -1 if 
 * there is any error.
 **/
int graph_getNumberOfEdges(const Graph *g){
    if(!g) return -1;
    return g->num_edges;
}

/**
 * @brief Determines if there is a connection between a pair of vertices.
 *
 * @param g Pointer to the graph.
 * @param orig ID of the origin vertex.
 * @param dest ID of the destination vertex.
 *
 * @return Returns TRUE if there is a connection in g from orig
 *  to dest, FALSE otherwise.
 **/
Bool graph_connectionExists(const Graph *g, long orig, long dest){
    if(!g) return ERROR;
    int i,j,origen,destino;
    for(i = 0; i < g->num_vertices; i++){
        if(vertex_getId(g->vertices[i]) == orig) origen = i;
        if(vertex_getId(g->vertices[i]) == destino) destino = i;
    }
    return (g->connections[i][j]);

}

/**
 * @brief Gets the number of connections starting at a given vertex.
 *
 * @param g Pointer to the graph.
 * @param id ID of the origin vertex.
 *
 * @return Returns the total number of connections starting at 
 * vertex with ID id, or -1 if there is any error.
 **/
int graph_getNumberOfConnectionsFromId(const Graph *g, long id){
    if(!g) return -1;
    int i,pos_orig,sum = 0;
    for(i = 0; i < g->num_vertices ;i++){
        if(vertex_getId(g->vertices[i]) == id) pos_orig = i; break;
    }
    for(i = 0; i < g->num_vertices ; i++){
        if(g->connections[pos_orig][i]) sum++;
    }
    return sum;


}

/**
 * @brief Returns an array with the ids of all the vertices which a 
 * given vertex connects to.
 *
 * This function allocates memory for the array.
 *
 * @param g Pointer to the graph.
 * @param id ID of the origin vertex.
 *
 * @return Returns an array with the ids of all the vertices to which 
 * the vertex with ID id is connected, or NULL if there is any error.
 */
long *graph_getConnectionsFromId(const Graph *g, long id){

}

/**
 * @brief Gets the number of connections starting at a given vertex.
 *
 * @param g Pointer to the graph.
 * @param tag Tag of the origin vertex.
 *
 * @return Returns the total number of connections starting at 
 * vertex with Tag tag, or -1 if there is any error.
 **/
int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag){
    if(!g ||!tag) return -1;
    int i,pos_orig,sum = 0;
    for(i = 0; i < g->num_vertices ;i++){
        if(vertex_getTag(g->vertices[i]) == tag) pos_orig = i; break;
    }
    for(i = 0; i < g->num_vertices ; i++){
        if(g->connections[pos_orig][i]) sum++;
    }
    return sum;
}

/**
 * @brief Returns an array with the ids of all the vertices which a 
 * given vertex connects to.
 *
 * This function allocates memory for the array.
 *
 * @param g Pointer to the graph.
 * @param tag Tag of the origin vertex.
 *
 * @return Returns an array with the ids of all the vertices to which 
 * the vertex with Tag tag is connected, or NULL if there is any error.
 */
long *graph_getConnectionsFromTag(const Graph *g, char *tag);

/**
 * @brief Prints a graph.
 *
 * Prints the graph g to the file pf.
 * The format to be followed is: print a line by vertex with the 
 * information associated with the vertex and the id of their connections:
 *
 * For example:
 * [1, Madrid, 0]: [2, Toledo, 0] [3, Avila, 0] 
 * [2, Toledo, 0]: [4, Segovia, 0] 
 * [3, Avila, 0]: 
 * [4, Segovia, 0]: [3, Avila, 0]
 *
 * @param pf File descriptor.
 * @param g Pointer to the graph.
 *
 * @return The number of characters printed, or -1 if there is any error.
 */
int graph_print (FILE *pf, const Graph *g){
    if(!pf ||!g) return -1;
    int i,j,printed,total = 0;
    for(i = 0; i < g->num_vertices; i++){
        printed = vertex_print(pf,g->vertices[i]);
        if( printed == -1) return -1;
        total += printed;
        fprintf(pf,": ");
        total ++;
        for(j = 0; j < g->num_vertices; j++){
            if(g->connections[i][j]) {
                printed = vertex_print(pf,g->vertices[j]);
                if(printed == -1) return -1;
                total += printed;
                
            }
            
        }
        fprintf(pf,"\n");
    }
    return total;
}


/**
 * @brief Reads a graph definition from a text file.
 *
 * Reads a graph description from the text file pointed to by fin,
 * and fills the graph g.
 *
 * The first line in the file contains the number of vertices.
 * Then one line per vertex with the vertex description.  
 * Finally one line per connection, with the ids of the origin and 
 * the destination. 
 *
 * For example:
 *
 * 4
 * id:1 tag:Madrid
 * id:2 tag:Toledo
 * id:3 tag:Avila
 * id:4 tag:Segovia
 * 1 2
 * 1 3
 * 2 4
 * 4 3
 *
 * @param fin Pointer to the input stream.
 * @param g Pointer to the graph.
 *
 * @return OK or ERROR
 */
Status graph_readFromFile (FILE *fin, Graph *g);