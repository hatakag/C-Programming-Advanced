#include <stdio.h>
#include <stdlib.h>
#include "jrb.h"
#include "jval.h"
#include "dllist.h"

typedef struct {
   JRB edges;
   JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2);
int hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
int DAG(Graph graph);
void dropGraph(Graph graph);
void topologicalSort(Graph g,int *output,int *n);
