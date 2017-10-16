#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 10

typedef union {
  int i;
  long l;
  float f;
  double d;
  void *v;
  char *s;
  char c;
}Jval;

Jval new_jval_i(int i) {Jval j;j.i=i;return j;}
Jval new_jval_l(long l) {Jval j;j.l=l;return j;}
Jval new_jval_f(float f) {Jval j;j.f=f;return j;}
Jval new_jval_d(double d) {Jval j;j.d=d;return j;}
Jval new_jval_v(void *v) {Jval j;j.v=v;return j;}
Jval new_jval_s(char *s) {Jval j;strcpy(j.s,s);return j;}
Jval new_jval_c(char c) {Jval j;j.c=c;return j;}

int jval_i(Jval j) {return j.i;}
long jval_l(Jval j) {return j.l;}
float jval_f(Jval j) {return j.f;}
double jval_d(Jval j) {return j.d;}
void *jval_v(Jval j) {return j.v;}
char *jval_s(Jval j) {return j.s;}
char jval_c(Jval j) {return j.c;}

void gen_exch(Jval *buf,int i,int j) {
  int size=sizeof(Jval);
  void *temp=malloc(size);
  if (size>0 && i>=0 && j>=0) {
    //assert(temp);
    memcpy(temp,(char*)buf+size*i,size);
    memcpy((char*)buf+size*i,(char*)buf+size*j,size);
    memcpy((char*)buf+size*j,temp,size);
  }
  free(temp);
}

void gen_qsort(Jval *a,int l,int r,int (*compare)(Jval*,Jval*)) {
  int size=sizeof(Jval);
  if (r<=l) return;
  int i=l-1,j=r;
  int p=l-1,q=r;
  while (1) {
    while (compare((char*)a+(++i)*size,(char*)a+r*size)<0);
    while (compare((char*)a+r*size,(char*)a+(--j)*size)<0)
      if (j==l) break;
    if (i>=j) break;
    gen_exch(a,i,j);
    if (compare((char*)a+i*size,(char*)a+r*size)==0)
      gen_exch(a,++p,i);
    if (compare((char*)a+j*size,(char*)a+r*size)==0)
      gen_exch(a,--q,j);
  }
  gen_exch(a,i,r);
  j=i-1;
  i=i+1;
  int k;
  for (k=l;k<=p;k++) gen_exch(a,k,j--);
  for (k=r-1;k>=q;k--) gen_exch(a,k,i++);
  gen_qsort(a,l,j,compare);
  gen_qsort(a,i,r,compare);
}

int search(Jval *a,int l,int r,Jval item,int (*compare)(Jval*,Jval*)) {
  int size=sizeof(Jval);
  if (r<l) return -1;
  int i,res;
  i=(l+r)/2;
  res = compare(&item,(char*)a+(size*i));
  if (res==0) return i;
  else if (res<0) 
    return search(a,l,i-1,item,compare);
  else 
    return search(a,i+1,r,item,compare); 
}

int compare_i(Jval *x,Jval *y){
  return (jval_i(*x)-jval_i(*y));
}

void sort_i(Jval *a,int l,int r) {
  gen_qsort(a,l,r,compare_i);
}

int search_i(Jval *a,int l,int r,int x) {
  return search(a,l,r,new_jval_i(x),compare_i);
}

Jval* create_array_i(int n) {
  int i;
  Jval* array=(Jval*)malloc(sizeof(Jval)*n);
  srand(time(NULL));
  for (i=0;i<n;i++) array[i]=new_jval_i(rand()%10);
  return array;
}

int main() {
  Jval *a=create_array_i(N);
  int i,item=5,res;
  for (i=0;i<N;i++) {printf("%d ",a[i].i);}
  printf("\n");
  sort_i(a,0,N-1);
  for (i=0;i<N;i++) printf("%d ",a[i].i);
  printf("\n");
  res=search_i(a,0,N-1,item);
  printf("res=%d\n",res);
  free(a);
  return 0;
}
