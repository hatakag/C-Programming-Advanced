#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//int (*compare)(void * item1,void * item2){}

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

int main(){
  int a[10],item=5;
  int n=10;
  int i,res;
  srand(time(NULL));
  for (i=0;i<n;i++) {a[i]=rand()%10;printf("%d ",a[i]);}
  printf("\n");
  qsort(a,n,sizeof(int),int_compare);
  for (i=0;i<n;i++) printf("%d ",a[i]);
  printf("\n");
  res=search(a,sizeof(int),0,n-1,&item,int_compare); //change int_compare function for other data type
  printf("res=%d\n",res);
  return 0;
}
