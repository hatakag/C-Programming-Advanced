#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

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

int main() {
  int i=0;
  type *a,*b,*c;
  a=(type*)malloc(N*sizeof(type));
  b=(type*)malloc(N*sizeof(type));
  c=(type*)malloc(N*sizeof(type));  
  srand(time(NULL));
  for (i=0;i<N;i++) {a[i]=rand()%10;b[i]=a[i];c[i]=a[i];}
  for (i=0;i<N;i++) printf("%d ",a[i]);
  printf("\n\n\n");
  
  clock_t start=clock();
  sort_3way_rev(a,0,N-1);
  clock_t finish=clock();
  double duration=(double)(finish-start)/CLOCKS_PER_SEC;
  for (i=0;i<N;i++) printf("%d ",a[i]);
  printf("\n");
  printf("Duration: %f\n",duration);
  
  printf("\n\n\n");
  start=clock();
  sort_2way_rev(b,0,N-1);
  finish=clock();
  duration=(double)(finish-start)/CLOCKS_PER_SEC;
  for (i=0;i<N;i++) printf("%d ",b[i]);
  printf("\n");
  printf("Duration: %f\n",duration);

  printf("\n\n\n");
  start=clock();
  qsort(c,N,sizeof(type),cmp_func);
  finish=clock();
  duration=(double)(finish-start)/CLOCKS_PER_SEC;
  for (i=0;i<N;i++) printf("%d ",c[i]);
  printf("\n");
  printf("Duration: %f\n",duration);

  free(a);
  free(b);
  free(c);
  return 0;
}
