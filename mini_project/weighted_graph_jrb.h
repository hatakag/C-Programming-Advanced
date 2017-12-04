#ifndef WEIGHTED_GRAPH_JRB_H
#define WEIGHTED_GRAPH_JRB_H

#include <stdio.h>
#include <stdlib.h>
#include "jrb.h"
#include "jval.h"
#include "dllist.h"

#define INFINITIVE_VALUE 1000

typedef struct {
   JRB edges;
   JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2,double weight); 
int hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
int DAG(Graph graph);
void dropGraph(Graph graph);
void BFS(Graph graph,int start,int stop,void (*func)(int));
void DFS(Graph graph,int start,int stop,void (*func)(int));
void BFS2(Graph graph,int start,int stop,void (*func)(int));
void DFS2(Graph graph,int start,int stop,void (*func)(int));
void topologicalSort(Graph g,int *output,int *n);
double getEdgeValue(Graph g,int v1,int v2); // return INFINITIVE_VALUE if no edge between v1 and v2
double shortestPath(Graph graph, int s, int t, int* path, int* length); // return the total weight of the path and the path is given via path and its length. Return INFINITIVE_VALUE if no path is found 

#endif
