#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "stack.h"
#include "types.h"
#include "queue.h"

#define MAX_VTX 4096
struct _Graph
{
    Vertex *vertices[MAX_VTX];          /*<!Array of pointers to vertex*/
    Bool connections[MAX_VTX][MAX_VTX]; /*<!Matrix with connections of the vertex*/
    int num_vertices;                   /*<!Number of vertex in the graph*/
    int num_edges;                      /*<!Number of edges in the graph*/
};

/*PRIVATE FUNCTIONS*/
/**
 * @brief sets all vertices of a graph to a determined state
 * 
 * @param g pointer to the graph
 * @param l the new state of the vertices
 */
Status _graph_setVertexState (Graph *g, Label l);

/**
 * @brief returns the vertex with a given Id in the graph
 * 
 * @param g pointer to the graph
 * @param vertexId id of the desired vertex
 * @return vertex with the given id
 */
Vertex *_graph_findVertexById(Graph *g, long id);
/*END OF PRIVATE FUNCTIONS*/

/*IMPLEMENTATION OF PRIVATE FUNCTIONS*/
Status _graph_setVertexState (Graph *g, Label l){
    int i;
    if(!g) return ERROR;

    for(i=0;i<graph_getNumberOfVertices(g);i++){
        if(!(vertex_setState(g->vertices[i], l))){
            return ERROR;
        }
    }
    return OK;
}

Vertex *_graph_findVertexById(Graph *g, long id){
    int i;
    if(!g || !id) return NULL;

    for(i=0;i<graph_getNumberOfVertices(g);i++){
        if(vertex_getId(g->vertices[i]) == id){
            return g->vertices[i];
        }
    }
    return NULL;
}
/*END OF IMPLEMENTATION OF PRIVATE FUNCTIONS*/
Graph *graph_init()
{
    int i, j;
    Graph *graph = NULL;
    graph = (Graph *)malloc(sizeof(Graph));
    if (!graph)
        return NULL;
    graph->num_vertices = 0;
    graph->num_edges = 0;
    for(i = 0; i < MAX_VTX; i++){
        for(j = 0; j < MAX_VTX; j++){
            graph->connections[i][j] = FALSE;
        }
    }
    return graph;
}

void graph_free(Graph *g)
{
    int i;
    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->vertices[i])
            free(g->vertices[i]);
    }
    free(g);
}

Status graph_newVertex(Graph *g, char *desc, int index)
{
    int i;
    Vertex *newVertex = NULL;
    if (!g)
        return ERROR;

    newVertex = vertex_initFromString(desc);

    if(!newVertex){
        return ERROR;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (vertex_cmp(newVertex,(g->vertices[i])) == 0)
        { /*Checks if the vertex is already created*/
            vertex_free(newVertex);
            return OK;
        }
    }

    if(!(vertex_setIndex(newVertex, index))){
        vertex_free(newVertex);
        return ERROR;
    }
    g->num_vertices++;
    g->vertices[g->num_vertices - 1] = newVertex;
    return OK;
}

Status graph_newEdge(Graph *g, long orig, long dest)
{
    Bool found = FALSE;
    int pos_orig = -1, pos_dest = -1, i;
    
    if(!g || orig < 1 || dest < 1){
        return ERROR;
    }
    
    if (graph_contains(g, orig) == FALSE || graph_contains(g, dest) == FALSE)
    {
        return ERROR;
    }
    for (i = 0; i < g->num_vertices && !found; i++)
    {
        if (orig == vertex_getId((g->vertices[i])))
        {
            pos_orig = i;
        }
        if (dest == vertex_getId((g->vertices[i])))
        {
            pos_dest = i;
        }
        if(pos_orig != -1 && pos_dest != -1){
            found=TRUE;
        }
    }
    if (pos_orig == -1 || pos_dest == -1)
    {
        return ERROR;
    }
    (g->num_edges)++;
    g->connections[pos_orig][pos_dest] = TRUE;
    return OK;
}

Bool graph_contains(const Graph *g, long id)
{   
    int i;
    if (!g || id < 1)
        return FALSE;
    for (i = 0; i < g->num_vertices; i++)
    {
        if (id == vertex_getId((g->vertices)[i]))
        {
            return TRUE;
        }
    }
    return FALSE;
}

int graph_getNumberOfVertices(const Graph *g)
{
    if (!g)
        return -1;
    return g->num_vertices;
}

int graph_getNumberOfEdges(const Graph *g)
{
    if (!g)
        return -1;
    return g->num_edges;
}

Bool graph_connectionExists(const Graph *g, long orig, long dest)
{
    int i, pos_orig = -1, pos_dest = -1;
    Bool found=FALSE;

    if (!g || orig < 1 || dest < 1)
        return FALSE;
    for (i = 0; i < g->num_vertices && !found; i++)
    {
        if (vertex_getId(g->vertices[i]) == orig){
            pos_orig = i;
        }
            
        if (vertex_getId(g->vertices[i]) == dest){
            pos_dest = i;
        }
        
        if(pos_dest != -1 && pos_orig != -1){
            found = TRUE;
        }
    }
    if (pos_orig == -1 || pos_dest == -1)
    {
        return FALSE;
    }
    return (g->connections[pos_orig][pos_dest]);
}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id)
{
    int i, pos_orig = -1, sum = 0;
    if (!g || id < 1)
        return -1;
    for (i = 0; (i < g->num_vertices) && (pos_orig == -1); i++)
    {
        if (vertex_getId(g->vertices[i]) == id)
        {
            pos_orig = i;
        }
    }
    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[pos_orig][i])
            sum++;
    }
    return sum;
}

long *graph_getConnectionsFromId(const Graph *g, long id)
{   
    int vtx_pos = -1, i, array_index = 0;
    long *connections=NULL;
    if (!g)
        return NULL;

    /*Makes sure the vertex is in the graph*/
    for (i = 0; i < g->num_vertices && vtx_pos == -1; i++)
    {
        if (id == vertex_getId(g->vertices[i]))
        {
            vtx_pos = i;
        }
    }
    if (vtx_pos == -1){
        return NULL;
    }

    connections = (long *)calloc(sizeof(long), graph_getNumberOfConnectionsFromId(g, id));
    
    if(!connections){
        return NULL;
    }

    for (i = 0; i < g->num_vertices; i++)
    {   /*En la fila del vértice que tiene el tag que se nos ha pasado como argumento, vamos recorriendo los vértices para ver cuál está conectado con ese. Como las posiciones en esa fila son iguales que en el array de vértices de g, usamos ese mismo índice para guardar el Id del vértice conectado en el array connections */
        if (g->connections[vtx_pos][i] > 0)
        { /*Usamos la variable array_index para llevar la cuenta del número de elementos que hemos metido en connections*/
            connections[array_index] = vertex_getId(g->vertices[i]);
            array_index++;
        }
    }

    return connections;
}

int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag)
{
    int i, pos_orig = -1, sum = 0;
    if (!g || !tag)
        return -1;
    for (i = 0; i < g->num_vertices; i++)
    {
        if (!strcmp(vertex_getTag(g->vertices[i]), tag))
        {
            pos_orig = i;
            break;
        }
    }
    if (pos_orig == -1)
        return -1;
    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[pos_orig][i])
            sum++;
    }
    return sum;
}

long *graph_getConnectionsFromTag(const Graph *g, char *tag)
{
    int vtx_pos, i, array_index = 0;
    Bool found = FALSE;
    long *connections=NULL;
    if (!g)
        return NULL;

    for (i = 0; i < g->num_vertices && !found; i++)
    {
        if (!strcmp(vertex_getTag(g->vertices[i]), tag))
        {
            vtx_pos = i;
            found = TRUE;
        }
    }
    if (!found)
        return NULL;
    /*Pongo sizeof(long) o sizeof(vertex_getId(un vértice cualquiera))*/
    connections = (long *)calloc(sizeof(long), graph_getNumberOfConnectionsFromTag(g, tag));

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[vtx_pos][i] > 0)
        { /*En la fila del vértice que tiene el tag que se nos ha pasado como argumento, vamos recorriendo los vértices para ver cuál está conectado con ese. Como las posiciones en esa fila son iguales que en el array de vértices de g, usamos ese mismo índice para guardar el Id del vértice conectado en el array connections */
            connections[array_index] = vertex_getId(g->vertices[i]);
            array_index++;
        }
    }

    return connections;
}

int graph_print(FILE *pf, const Graph *g)
{
    int i, j, printed, total = 0;
    if (!pf || !g)
        return -1;
    for (i = 0; i < g->num_vertices; i++)
    {
        printed = vertex_print(pf, g->vertices[i]);
        if (printed == -1)
            return -1;
        total += printed;
        fprintf(pf, ": ");
        total++;
        total++;
        for (j = 0; j < g->num_vertices; j++)
        {
            if (g->connections[i][j])
            {
                printed = vertex_print(pf, g->vertices[j]);
                if (printed == -1)
                    return -1;
                total += printed;
            }
        }
        fprintf(pf, "\n");
        total++;
    }
    return total;
}

Status graph_readFromFile(FILE *fin, Graph *g)
{
    int i, t;
    long id1, id2;
    char line[MAX_CHARS_IN_LINE];
    if (!g || !fin){
        return ERROR;
    }


    fgets(line, MAX_CHARS_IN_LINE, fin);
    t = atoi(line);

    if(t<=0 || t>MAX_VTX){
        return ERROR;
    }
    for (i = 0; i < t; i++)
    {
        if (!fgets(line, MAX_CHARS_IN_LINE, fin))
        {
            return ERROR;
        }
        if (graph_newVertex(g, line, i) == ERROR)
        {
            return ERROR;
        }
    }

    g->num_edges = 0;
    while (fscanf(fin, "%ld %ld", &id1, &id2) == 2)
    {
        if (graph_newEdge(g, id1, id2) == ERROR)
        {
            return ERROR;
        }
    }

    return OK;
}

Status graph_depthSearch(Graph *g, long from_id, long to_id){
    int i;
    Status st=OK;
    Stack *s=NULL;
    Vertex *vf=NULL, *vt=NULL, *v0=NULL, *v=NULL;
    long *adj_vert=NULL;

    if(!g || !from_id || !to_id){
        return ERROR;
    }
    if((_graph_setVertexState(g, WHITE) == ERROR)){
        return ERROR;
    }

    /*Creation of the stack*/
    s=stack_init();
    if(!s){
        return ERROR;
    }

    /*We get the vertices that correspond to the given id's*/
    vf = _graph_findVertexById(g, from_id);
    vt = _graph_findVertexById(g, to_id);

    if(!vt || !vf){
        stack_free(s);
        return ERROR;
    }

    if(!(vertex_setState(vf, BLACK))){
        stack_free(s);
        return ERROR;
    }
    if(!stack_push(s, (void *)vf)){
        stack_free(s);
        return ERROR;
    }
    
    while(stack_isEmpty(s)==FALSE && st==OK){
        v0 = (Vertex *)stack_pop(s);
        if(!v0){
            st = ERROR;
            break;
        }
        printf("\n");
        vertex_print(stdout, v0);
        
        if(vertex_cmp(v0, vt) == 0){
            st=END;
        }else{
            adj_vert = graph_getConnectionsFromId(g, vertex_getId(v0));
            if(!adj_vert){
                st = ERROR;
            }
            for(i=0;i<graph_getNumberOfConnectionsFromId(g, vertex_getId(v0)) && st==OK;i++){
                v = _graph_findVertexById(g, adj_vert[i]);
                if(!v){
                    st = ERROR;
                }
                if(vertex_getState(v)==WHITE){
                    vertex_setState(v, BLACK);
                    if(!(stack_push(s, (void *)v))){
                        st = ERROR;
                    }
                }
            }
            free(adj_vert);
            adj_vert = NULL;
        }
    }
    if(adj_vert != NULL){
        free(adj_vert);
    }
    stack_free(s);
    return st;
}

long *_graph_get_connections(const Graph *g, int ix){
    if(!g || ix<0){
        return NULL;
    }
    return graph_getConnectionsFromId(g, vertex_getId(g->vertices[ix]));
}

int _graph_getNumConnections(const Graph *g, int ix){
    if(!g || ix<0){
        return -1;
    }
    return graph_getNumberOfConnectionsFromId(g, vertex_getId(g->vertices[ix]));
}


Status graph_breathSearch(Graph *g, long from_id, long to_id){
    int i;
    Status st=OK;
    Stack *queue=NULL;
    Vertex *vf=NULL, *vt=NULL, *v0=NULL, *v=NULL;
    long *adj_vert=NULL;

    if(!g || !from_id || !to_id){
        return ERROR;
    }
    if((_graph_setVertexState(g, WHITE) == ERROR)){
        return ERROR;
    }

    /*Creation of the stack*/
    queue=queue_init();
    if(!queue){
        return ERROR;
    }

    /*We get the vertices that correspond to the given id's*/
    vf = _graph_findVertexById(g, from_id);
    vt = _graph_findVertexById(g, to_id);

    if(!vt || !vf){
        queue_free(queue);
        return ERROR;
    }

    if(!(vertex_setState(vf, BLACK))){
        queue_free(queue);
        return ERROR;
    }
    if(!queue_push(queue, (void *)vf)){
        queue_free(queue);
        return ERROR;
    }
    
    while(queue_isEmpty(queue)==FALSE && st==OK){
        v0 = (Vertex *)queue_pop(queue);
        if(!v0){
            st = ERROR;
            break;
        }
        printf("\n");
        vertex_print(stdout, v0);
        
        if(vertex_cmp(v0, vt) == 0){
            st=END;
        }else{
            adj_vert = graph_getConnectionsFromId(g, vertex_getId(v0));
            if(!adj_vert){
                st = ERROR;
            }
            for(i=0;i<graph_getNumberOfConnectionsFromId(g, vertex_getId(v0)) && st==OK;i++){
                v = _graph_findVertexById(g, adj_vert[i]);
                if(!v){
                    st = ERROR;
                }
                if(vertex_getState(v)==WHITE){
                    vertex_setState(v, BLACK);
                    if(!(queue_push(queue, (void *)v))){
                        st = ERROR;
                    }
                }
            }
            free(adj_vert);
            adj_vert = NULL;
        }
    }
    if(adj_vert != NULL){
        free(adj_vert);
    }
    queue_free(queue);
    return st;
}