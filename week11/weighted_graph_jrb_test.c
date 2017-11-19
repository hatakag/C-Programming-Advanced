#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "weighted_graph_jrb.h"

void printVertices(int v) {printf("%d ",v);}

int main() {
  Graph g=createGraph();
  addVertex(g,0,"V0");
  addVertex(g,1,"V1");
  addVertex(g,2,"V2");
  addVertex(g,3,"V3");
  addVertex(g,4,"V4");
  addVertex(g,5,"V5");
  addVertex(g,6,"V6");
  addVertex(g,7,"V7");
  addEdge(g,0,1,10);
  addEdge(g,1,2,9);//
  addEdge(g,2,4,13);
  addEdge(g,1,3,7);
  addEdge(g,0,5,6);//
  addEdge(g,3,4,8);//
  addEdge(g,5,4,30);
  addEdge(g,5,2,2);

  /*
  int i,n1,n2,n3,output1[100],output2[100],output3[100];
  n1=indegree(g,5,output1);
  for (i=0;i<n1;i++) {
    printf("%d ",output1[i]);
  }
  printf("\n");
  n2=outdegree(g,5,output2);
  for (i=0;i<n2;i++) {
    printf("%d ",output2[i]);
  }
  printf("\n");
  if (DAG(g)) printf("The graph is acycle\n");
  else printf("Have cycles in the graph\n");
  if (!DAG(g)) {printf("Cannot make topological sort\n");}
  else {
    topologicalSort(g,output3,&n3);
    printf("The topological order:\n");
    for (i=0;i<n3;i++) {
      printf("%d ",output3[i]);
    }
    printf("\n%d\n",n3);
    for (i=0;i<n3;i++) {
      printf("%s ",getVertex(g,output3[i]));
    }
  }
  printf("\n");
  printf("\nBFS : ");BFS(g,0,5,printVertices);
  printf("\nBFS2: ");BFS2(g,0,5,printVertices);
  printf("\nDFS : ");DFS(g,0,5,printVertices);
  printf("\nDFS2: ");DFS2(g,0,5,printVertices);
  printf("\n");
  */

  //
  double d;
  int i,path[100],length,s=0,t=4;
  d=shortestPath(g,s,t,path,&length);
  
  printf("\n____GRAPH1____\n");
  if (d==INFINITIVE_VALUE) printf("\nNo path between %d and %d\n",s,t);
  else {
    printf("\nShortest path from %s to %s: \n",getVertex(g,s),getVertex(g,t));
    for (i=0;i<length;i++) {
      printf("%s(%d) ",getVertex(g,path[i]),path[i]);
    }
    printf("\n");
    printf("Distance: %f\n",d);
  }
  
  dropGraph(g);

  Graph g2=createGraph();
  addVertex(g2,0,"V0");
  addVertex(g2,1,"V1");
  addVertex(g2,2,"V2");
  addVertex(g2,3,"V3");
  addVertex(g2,4,"V4");
  addVertex(g2,5,"V5");
  addVertex(g2,6,"V6");
  addVertex(g2,7,"V7");
  addEdge(g2,1,2,9);
  addEdge(g2,1,6,14);
  addEdge(g2,1,7,15);
  addEdge(g2,2,3,24);
  addEdge(g2,6,3,18);
  addEdge(g2,6,5,30);
  addEdge(g2,6,7,5);
  addEdge(g2,7,5,20);
  addEdge(g2,7,0,44);
  addEdge(g2,3,5,2);
  addEdge(g2,3,0,19);
  addEdge(g2,5,4,11);
  addEdge(g2,5,0,16);
  addEdge(g2,4,3,6);
  addEdge(g2,4,0,6);

  s=1,t=0;
  d=shortestPath(g2,s,t,path,&length);
  
  printf("\n____GRAPH2____\n");
  if (d==INFINITIVE_VALUE) printf("\nNo path between %d and %d\n",s,t);
  else {
    printf("\nShortest path from %s to %s: \n",getVertex(g2,s),getVertex(g2,t));
    for (i=0;i<length;i++) {
      printf("%s(%d) ",getVertex(g2,path[i]),path[i]);
    }
    printf("\n");
    printf("Distance: %f\n\n",d);
  }
  
  dropGraph(g2);

  return 0;
}
