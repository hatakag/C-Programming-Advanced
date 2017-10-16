#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 10
#define MAX 10

typedef int type;

void exch(type a[],int i,int j) {
  type tmp;
  tmp=a[j];
  a[j]=a[i];
  a[i]=tmp;
}

void sort_3way(type a[],int l,int r) {
  if (r<=l) return ;
  int i=l-1,j=r;
  int p=l-1,q=r;
  while (1) {
    while (a[++i] < a[r]);
    while (a[r] < a[--j]) if (j==1) break;
    if (i>=j) break;
    exch(a,i,j);
    if (a[i]==a[r]) exch(a,++p,i);
    if (a[j]==a[r]) exch(a,--q,j);
  }
  exch(a,i,r);
  j=i-1;
  i=i+1;
  int k;
  for (k=l;k<=p;k++) exch(a,k,j--);
  for (k=r-1;k>=q;k--) exch(a,k,i++);
  sort_3way(a,l,j);
  sort_3way(a,i,r);
}

void sort_2way(type a[],int l,int r) {
  if (r<=l) return ;
  int i=l-1,j=r;
  while (1) {
    while (a[++i] < a[r]);
    while (a[r] < a[--j]) if (j==1) break;
    if (i>=j) break;
    exch(a,i,j);
  }
  exch(a,i,r);
  j=i-1;
  i=i+1;
  sort_2way(a,l,j);
  sort_2way(a,i,r);
}

void sort_3way_rev(type a[],int l,int r) {
  if (r<=l) return ;
  int i=l-1,j=r;
  int p=l-1,q=r;
  while (1) {
    while (a[++i] > a[r]);
    while (a[r] > a[--j]) if (j==1) break;
    if (i>=j) break;
    exch(a,i,j);
    if (a[i]==a[r]) exch(a,++p,i);
    if (a[j]==a[r]) exch(a,--q,j);
  }
  exch(a,i,r);
  j=i-1;
  i=i+1;
  int k;
  for (k=l;k<=p;k++) exch(a,k,j--);
  for (k=r-1;k>=q;k--) exch(a,k,i++);
  sort_3way_rev(a,l,j);
  sort_3way_rev(a,i,r);
}

void sort_2way_rev(type a[],int l,int r) {
  if (r<=l) return ;
  int i=l-1,j=r;
  while (1) {
    while (a[++i] > a[r]);
    while (a[r] > a[--j]) if (j==1) break;
    if (i>=j) break;
    exch(a,i,j);
  }
  exch(a,i,r);
  j=i-1;
  i=i+1;
  sort_2way_rev(a,l,j);
  sort_2way_rev(a,i,r);
}

int cmp_func(const void *a,const void *b) {
  return ( *(type*)a - *(type*)b );
}

int cmp_func_rev(const void *a,const void *b) {
  return ( *(type*)b - *(type*)a );
}

type *createArray(int size){
  int i=0;
  type *a;
  a=(type*)malloc(size*sizeof(type));
  srand(time(NULL));
  for (i=0;i<size;i++) {
    a[i]=rand()%MAX;
    //printf("%d ",a[i]);
  }
  return a;
}

type *dumpArray(type *p,int size) {
  type *a;
  a=(type*)malloc(size*sizeof(type));
  memcpy(a,p,size*sizeof(type));
  return a;
}

int main() {
  type *a,*b,*c,*d,*e,*f,*g;
  a=createArray(N);
  b=dumpArray(a,N);
  c=dumpArray(a,N);
  d=dumpArray(a,N);
  e=dumpArray(a,N);
  f=dumpArray(a,N);
  g=dumpArray(a,N);
  printf("Original list: ");
  int i=0;
  for(i=0;i<N;i++) {
    printf("%d ",b[i]);
  }
  printf("\n");
  // 
  printf("\n");
  printf("Quick sort 3 way partition ascendant: ");
  clock_t start=clock();
  sort_3way(b,0,N-1);
  clock_t finish=clock();
  double duration=(double)(finish-start)/CLOCKS_PER_SEC;
  for (i=0;i<N;i++) printf("%d ",b[i]);
  printf("\n");
  printf("Duration: %f\n",duration);
  // 
  printf("\n\n");
  printf("Quick sort 2 way partition ascendant: ");
  start=clock();
  sort_2way(d,0,N-1);
  finish=clock();
  duration=(double)(finish-start)/CLOCKS_PER_SEC;
  for (i=0;i<N;i++) printf("%d ",d[i]);
  printf("\n");
  printf("Duration: %f\n",duration);
  //
  printf("\n\n");
  printf("Quicks sort (qsort()) ascendant: ");
  start=clock();
  qsort(f,N,sizeof(type),cmp_func);
  finish=clock();
  duration=(double)(finish-start)/CLOCKS_PER_SEC;
  for (i=0;i<N;i++) printf("%d ",f[i]);
  printf("\n");
  printf("Duration: %f\n",duration);
  //
  printf("\n\n");
  printf("Quick sort 3 way partition descendant: ");
  start=clock();
  sort_3way_rev(c,0,N-1);
  finish=clock();
  duration=(double)(finish-start)/CLOCKS_PER_SEC;
  for (i=0;i<N;i++) printf("%d ",c[i]);
  printf("\n");
  printf("Duration: %f\n",duration);
  //
  printf("\n\n");
  printf("Quick sort 2 way partition descendant: ");
  start=clock();
  sort_2way_rev(e,0,N-1);
  finish=clock();
  duration=(double)(finish-start)/CLOCKS_PER_SEC;
  for (i=0;i<N;i++) printf("%d ",e[i]);
  printf("\n");
  printf("Duration: %f\n",duration);
  //
  printf("\n\n");
  printf("Quicks sort (qsort()) descendant: ");
  start=clock();
  qsort(g,N,sizeof(type),cmp_func_rev);
  finish=clock();
  duration=(double)(finish-start)/CLOCKS_PER_SEC;
  for (i=0;i<N;i++) printf("%d ",g[i]);
  printf("\n");
  printf("Duration: %f\n",duration);
  //
  free(a);
  free(b);
  free(c);
  free(d);
  free(e);
  free(f);
  return 0;
}
