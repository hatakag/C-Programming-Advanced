#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "undirect_graph_jrb.h"

#define MAX_STATION 10
#define MAX_LINE 10

enum{SUCCESS,FAIL};

typedef struct {
  int number;
  char name[40];
}Station;


int main(int argc,char *argv[]){
  if (argc!=3) {
    printf("Wrong number of input\n");
    return 0;
  }
  int reval=SUCCESS;
  FILE *fp1,*fp2;
  if ((fp1=fopen(argv[1],"r"))==NULL) {      //staions
    printf("Can't open file %s\n",argv[1]);
    reval=FAIL;
  }
  if ((fp2=fopen(argv[2],"r"))==NULL) {      //lines
    printf("Can't open file %s\n",argv[2]);
    reval=FAIL;
  }
  
  Graph g;
  g=createGraph();
  
  //file station
  Station *s;
  s=(Station*)malloc(sizeof(Station)*MAX_STATION);
  int n=0;
  while (!feof(fp1)) {
    fscanf(fp1,"%*c %d %*c %[^\n]%*c",&s[n].number,s[n].name);
    n++;
    if (n>MAX_STATION) s=(Station*)realloc(s,sizeof(Station)*n);
  }
  s=(Station*)realloc(s,sizeof(Station)*n);
  fclose(fp1);
  
  //file line
  int *c,i,j;
  c=(int*)malloc(sizeof(int)*MAX_LINE);
  while (!feof(fp2)) {
    fgetc(fp2);fgetc(fp2);fgetc(fp2); // fgetc tra ve int->ASCII->char
    i=0;
    while (fgetc(fp2)=='S') {
      c[i++]=fgetc(fp2);
      if (fgetc(fp2)=='\n') break;
    }
    for (j=1;j<i;j++) addEdge(g,c[j-1]-48,c[j]-48);
  }
  free(c);
  fclose(fp2);
  
  char station[40],ch;
  int output[MAX_LINE],total;
  do {
    printf("Station: ");scanf("%[^\n]",station);__fpurge(stdin);
    for (j=0;j<n;j++) {
      if (strcmp(station,s[j].name)==0)
	total=getAdjacentVertices(g,s[j].number,output);
    }
    printf("Adjacent station(s) to that station: \n");
    for (j=0;j<total;j++) {
      for (i=0;i<n;i++) {
	if (output[j]==s[i].number)
	  printf("%s\n",s[i].name);
      }
    }
    printf("Continue (y or n): ");scanf("%c",&ch);__fpurge(stdin);
    if (ch=='n') break;
  }while(1);
  
  dropGraph(g);
  return reval;
}
