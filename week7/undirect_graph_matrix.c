#include "undirect_graph_matrix.h"

Graph createGraph(int sizemax) {
  Graph graph;
  graph.sizemax=sizemax;
  graph.matrix=(int*)malloc(sizeof(int)*sizemax*sizemax);
  int i,j;
  for (i=0;i<sizemax;i++)
    for (j=0;j<sizemax;j++)
      graph.matrix[i*graph.sizemax+j]=0;
  return graph;
}

void addEdge(Graph graph,int v1,int v2) {
  graph.matrix[graph.sizemax*v1+v2]=1;
  graph.matrix[graph.sizemax*v2+v1]=1;
}

int adjacent(Graph graph,int v1,int v2) {
  return graph.matrix[graph.sizemax*v1+v2] || graph.matrix[graph.sizemax*v2+v1];
}

int getAdjacentVertices(Graph graph,int vertex,int *output) {
  int i,j=0;
  for (i=0;i<graph.sizemax;i++) 
    if (adjacent(graph,vertex,i)==1) 
      output[j++]=i;
  return j;
}

void dropGraph(Graph graph){
  free(graph.matrix);
}
