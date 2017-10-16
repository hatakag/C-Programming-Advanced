#include <stdio.h>
#include "undirect_graph_jrb.h"

int main(){
  int i,n,output[100];
  Graph g=createGraph(100);
  addEdge(g,0,1);
  addEdge(g,0,2);
  addEdge(g,1,2);
  addEdge(g,1,3);
  addEdge(g,6,1);
  n=getAdjacentVertices(g,1,output);
  if (n==0) printf("No adjacent vertices of node 1\n");
  else {
    printf("Adjacent vertices of node 1: ");
    for (i=0;i<n;i++) printf("%5d",output[i]);
  }
  printf("\nn=%d\n",n);
  int j=adjacent(g,3,1);
  printf("j=%d\n",j);
  dropGraph(g);
  return 0;
}
