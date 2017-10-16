#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <assert.h>

#define N 10

void gen_exch(void *buf,int size,int i,int j) {
  void *temp=malloc(size);
  if (size>0 && i>=0 && j>=0) {
    //assert(temp);
    memcpy(temp,(char*)buf+size*i,size);
    memcpy((char*)buf+size*i,(char*)buf+size*j,size);
    memcpy((char*)buf+size*j,temp,size);
  }
  free(temp);
}

void gen_qsort(void *a,int size,int l,int r,int (*compare)(void const*,void const*)) {
  if (r<=l) return;
  int i=l-1,j=r;
  int p=l-1,q=r;
  while (1) {
    while (compare((char*)a+(++i)*size,(char*)a+r*size)<0);
    while (compare((char*)a+r*size,(char*)a+(--j)*size)<0)
      if (j==l) break;
    if (i>=j) break;
    gen_exch(a,size,i,j);
    if (compare((char*)a+i*size,(char*)a+r*size)==0)
      gen_exch(a,size,++p,i);
    if (compare((char*)a+j*size,(char*)a+r*size)==0)
      gen_exch(a,size,--q,j);
  }
  gen_exch(a,size,i,r);
  j=i-1;
  i=i+1;
  int k;
  for (k=l;k<=p;k++) gen_exch(a,size,k,j--);
  for (k=r-1;k>=q;k--) gen_exch(a,size,k,i++);
  gen_qsort(a,size,l,j,compare);
  gen_qsort(a,size,i,r,compare);
}

int search(void *buf,int size,int l,int r,void *item,int (*compare)(void const*,void const*)) {
  if (r<l) return -1;
  int i,res;
  i=(l+r)/2;
  res = compare(item,(char*)buf+(size*i));
  if (res==0) return i;
  else if (res<0) 
    return search(buf,size,l,i-1,item,compare);
  else 
    return search(buf,size,i+1,r,item,compare); 
}

int int_compare(void const *x,void const *y){
  return (*(int*)x - *(int*)y);
}

int main() {
  int a[10],item=5;
  int n=10;
  int i,res;
  srand(time(NULL));
  for (i=0;i<n;i++) {a[i]=rand()%10;printf("%d ",a[i]);}
  printf("\n");
  gen_qsort(a,sizeof(int),0,n-1,int_compare);
  //qsort(a,n,sizeof(int),int_compare);
  for (i=0;i<n;i++) printf("%d ",a[i]);
  printf("\n");
  res=search(a,sizeof(int),0,n-1,&item,int_compare); //change int_compare function for other data type
  printf("res=%d\n",res);
  return 0;
}
