#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "jval.h"
#include "dllist.h"
#include "weighted_graph_jrb.h"

enum{SUCCESS,FAIL};

void readFile(Graph g,FILE *fp1,FILE *fp2,int i) {
  while(!feof(fp1)) {
    char s[100];
    fscanf(fp1,"%s",s);
    JRB tmp;
    jrb_traverse(tmp,g.vertices) {
      if (strcmp(s,jval_s(tmp->val))!=0) {addVertex(g,i,s);i++;} 
    }
  }
  while(!feof(fp2)) {
    char s1[100],s2[100];
    double d;
    int v1,v2;
    fscanf(fp2,"%s",s1);
    fscanf(fp2,"%s",s2);
    fscanf(fp2,"%f",&d);
    JRB tmp;
    jrb_traverse(tmp,g.vertices) {
      if (strcmp(s1,jval_s(tmp->val))==0) v1=jval_i(tmp->key);
      if (strcmp(s2,jval_s(tmp->val))==0) v2=jval_i(tmp->key);
    }
    addEdge(g,v1,v2,d);
    addEdge(g,v2,v1,d);
  }
}

void printVertices(int v) {printf("%d",v);}

int main() {
  int reval;
  FILE *fp1;
  if ((fp1=fopen("go_station12.txt","r"))==NULL) {
    printf("Cannot open file %s\n","go_station12.txt");
    reval=FAIL;
  }
  FILE *fp2;
  if ((fp2=fopen("go_distance12.txt","r"))==NULL) {
    printf("Cannot open file %s\n","go_distance12.txt");
    reval=FAIL;
  }
  
  Graph g=createGraph();
  int i=0;
  readFile(g,fp1,fp2,i);
  printf("\nBFS : ");BFS(g,0,i,printVertices);
  printf("\n");
  return reval;
}
