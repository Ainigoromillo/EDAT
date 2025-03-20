#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#define MAX_VTX 4096
#define MAX_CHARS_IN_LINE 50
struct _Graph
{
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};


Graph *graph_init()
{
    Graph *graph = NULL;
    graph = (Graph *)malloc(sizeof(Graph));
    if (!graph)
        return NULL;
    graph->num_vertices = 0;
    graph->num_edges = 0;
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


Status graph_newVertex(Graph *g, char *desc)
{
    if (!g)
        return ERROR;
    int i, j = 0;
    Vertex *newVertex = NULL;
    newVertex = vertex_initFromString(desc);

    for (i = 0; i < g->num_vertices; i++)
    {
        if (vertex_getId(newVertex) == vertex_getId(g->vertices[i]))
        { /*Checks if the vertex is already created*/
            j = 1;
            break;
        }
    }
    if (j == 1)
    {
        return OK;
    }
    g->num_vertices++;
    g->vertices[g->num_vertices - 1] = newVertex;
    return OK;
}


Status graph_newEdge(Graph *g, long orig, long dest)
{
    Bool found = FALSE;
    int pos_orig = -1, pos_dest = -1;
    if (!graph_contains(g, orig) || !graph_contains(g, dest))
    {
        return ERROR;
    }
    for (int i = 0; i < g->num_vertices && !found; i++)
    {
        if (orig == vertex_getId((g->vertices[i])))
        {
            pos_orig = i;
        }
        if (dest == vertex_getId((g->vertices[i])))
        {
            pos_dest = i;
        }
    }
    if (pos_orig == -1 || pos_dest == -1)
    {
        return ERROR;
    }
    (g->num_edges)++;
    (g->connections[pos_orig][pos_dest])++;
    return OK;
}


Bool graph_contains(const Graph *g, long id)
{
    if (!g)
        return ERROR;
    for (int i = 0; i < g->num_vertices; i++)
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
    if (!g)
        return FALSE;
    int i, origen = -1, destino = -1;
    for (i = 0; i < g->num_vertices; i++)
    {
        if (vertex_getId(g->vertices[i]) == orig){
            origen = i;
        }
            
        if (vertex_getId(g->vertices[i]) == dest){
            destino = i;
        }
    }
    if (origen == -1 || destino == -1)
    {
        return FALSE;
    }
    return (g->connections[origen][destino]);
}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id)
{
    if (!g)
        return -1;
    int i, pos_orig, sum = 0;
    for (i = 0; i < g->num_vertices; i++)
    {
        if (vertex_getId(g->vertices[i]) == id)
        {
            pos_orig = i;
            break;
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
    if (!g)
        return NULL;
    int vtx_pos = -1, i, array_index = 0;
    long *connections;

    /*Makes sure the vertex is in the graph*/
    for (i = 0; i < g->num_vertices && vtx_pos == -1; i++)
    {
        if (id == vertex_getId(g->vertices[vtx_pos]))
        {
            vtx_pos = i;
        }
    }
    if (vtx_pos == -1)
        return NULL;
    /*Pongo sizeof(long) o sizeof(vertex_getId(un vértice cualquiera))*/
    connections = (long *)calloc(sizeof(long), graph_getNumberOfConnectionsFromId(g, id));

    for (i = 0; i < g->num_vertices; i++)
    { /*En la fila del vértice que tiene el tag que se nos ha pasado como argumento, vamos recorriendo los vértices para ver cuál está conectado con ese. Como las posiciones en esa fila son iguales que en el array de vértices de g, usamos ese mismo índice para guardar el Id del vértice conectado en el array connections */
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
    if (!g || !tag)
        return -1;
    int i, pos_orig = -1, sum = 0;
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
    if (!g)
        return NULL;
    int vtx_pos, i, array_index = 0;
    Bool found = FALSE;
    long *connections;

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
    if (!pf || !g)
        return -1;
    int i, j, printed, total = 0;
    for (i = 0; i < g->num_vertices; i++)
    {
        printed = vertex_print(pf, g->vertices[i]);
        if (printed == -1)
            return -1;
        total += printed;
        fprintf(pf, ": ");
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
    }
    return total;
}

Status graph_readFromFile(FILE *fin, Graph *g)
{

    if (!g || !fin)
        return ERROR;
    int i, t;
    long id1, id2;
    char line[MAX_CHARS_IN_LINE];

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
        if (graph_newVertex(g, line) == ERROR)
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