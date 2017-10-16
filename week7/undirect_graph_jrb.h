#include <stdio.h>
#include <stdlib.h>
#include "jrb.h"
#include "jval.h"

typedef JRB Graph;

Graph createGraph();
void addEdge(Graph graph,int v1,int v2);
int adjacent(Graph graph,int v1,int v2);
int getAdjacentVertices(Graph graph,int v,int *output);
void dropGraph(Graph graph);
