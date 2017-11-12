#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "direct_graph_jrb.h"

void printVertices(int v) {printf("%d ",v);}

enum{SUCCESS,FAIL};

int main(int argc, char* argv[]) {
  
  if (argc!=2) {
    printf("Wrong number of input\n");
    return 0;
  }
  int reval=SUCCESS;

  FILE *fp;
  if ((fp=fopen(argv[1],"r"))==NULL) {
    printf("Cannot open file %s\n",argv[1]);
    reval=FAIL;
  }
  
  Graph g=createGraph();
  int id_tmp,count;
  char s[10],id[10];
  while(!feof(fp)) {
    fscanf(fp,"%s %s",s,id);
    printf("%s %s\n",s,id);
    if (strcmp(s,"CLASS")==0) {
      addVertex(g,atoi(id+strlen(id)-3),id);
      //printf("addVertex %d %s\n",atoi(id+strlen(id)-3),id);
      id_tmp=atoi(id+strlen(id)-3);
    }
    if (strcmp(s,"PREREQ")==0) {
      addVertex(g,atoi(id+strlen(id)-3),id);
      //printf("addVertex %d %s\n",atoi(id+strlen(id)-3),id);
      addEdge(g,atoi(id+strlen(id)-3),id_tmp);
      //printf("addEdge %d %d\n",atoi(id+strlen(id)-3),id_tmp);
    }
    count++;
    if (feof(fp)) break;
  }
  fclose(fp);
  printf("%d\n",count);
  /*
  int i,n1,n2,output1[100],output2[100];
  n1=indegree(g,140,output1);
  for (i=0;i<n1;i++) {
    printf("%d ",output1[i]);
  }
  printf("\n");
  n2=outdegree(g,140,output2);
  for (i=0;i<n2;i++) {
  printf("%d ",output2[i]);
    }
  printf("\n");
  */
  int i,n,output[100];
  if (!DAG(g)) {printf("Cannot make topological sort\n");return 1;}
  topologicalSort(g,output,&n);
  printf("The topological order:\n");
  for (i=0;i<n;i++) {
    printf("%d ",output[i]);
  }
  printf("\n%d\n",n);
  for (i=0;i<n;i++) {
    printf("%s ",getVertex(g,output[i]));
  }
  printf("\n");
  
  dropGraph(g);
  return reval;
  
  /*
  int i,n1,n2,n3,output1[100],output2[100],output3[100];
  Graph g=createGraph();
  addVertex(g,0,"V0");
  addVertex(g,1,"V1");
  addVertex(g,2,"V2");
  addVertex(g,3,"V3");
  addVertex(g,4,"V4");
  addVertex(g,5,"V5");
  addEdge(g,0,1);
  addEdge(g,1,2);
  addEdge(g,2,4);
  addEdge(g,1,3);
  addEdge(g,5,2);
  addEdge(g,5,4);
  addEdge(g,0,1);
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
  if (!DAG(g)) {printf("Cannot make topological sort\n");return 1;}
  topologicalSort(g,output3,&n3);
  printf("The topological order:\n");
  for (i=0;i<n3;i++) {
    printf("%d ",output3[i]);
  }
  printf("\n%d\n",n3);
  for (i=0;i<n3;i++) {
    printf("%s ",getVertex(g,output3[i]));
  }
  printf("\n");
  printf("\nBFS : ");BFS(g,4,5,printVertices);
  printf("\nBFS2: ");BFS2(g,4,5,printVertices);
  printf("\nDFS : ");DFS(g,4,5,printVertices);
  printf("\nDFS2: ");DFS2(g,4,5,printVertices);
  printf("\n");
  dropGraph(g);
  return 0;
  */
}
