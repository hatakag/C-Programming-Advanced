#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

void exch(int a[],int i,int j) {
  int tmp;
  tmp=a[j];
  a[j]=a[i];
  a[i]=tmp;
}

void sort_3way(int a[],int l,int r) {
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

void sort_2way(int a[],int l,int r) {
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

int cmp_func(const void *a,const void *b) {
  return ( *(int*)a - *(int*)b );
}

int main() {
  int i=0;
  int *a,*b,*c;
  a=(int*)malloc(N*sizeof(int));
  b=(int*)malloc(N*sizeof(int));
  c=(int*)malloc(N*sizeof(int));  
  srand(time(NULL));
  for (i=0;i<N;i++) {a[i]=rand()%10;b[i]=a[i];c[i]=a[i];}
  for (i=0;i<N;i++) printf("%d ",a[i]);
  printf("\n\n\n");
  
  clock_t start=clock();
  sort_3way(a,0,N-1);
  clock_t finish=clock();
  double duration=(double)(finish-start)/CLOCKS_PER_SEC;
  for (i=0;i<N;i++) printf("%d ",a[i]);
  printf("\n");
  printf("Duration: %f\n",duration);
  
  printf("\n\n\n");
  start=clock();
  sort_2way(b,0,N-1);
  finish=clock();
  duration=(double)(finish-start)/CLOCKS_PER_SEC;
  for (i=0;i<N;i++) printf("%d ",b[i]);
  printf("\n");
  printf("Duration: %f\n",duration);

  printf("\n\n\n");
  start=clock();
  qsort(c,N,sizeof(int),cmp_func);
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
