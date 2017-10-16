#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {SUCCESS,FAIL};
typedef struct phoneaddress {
  char name[40];
  char tel[12];
}phone;

int cmp_func(const void *a,const void *b) {
  phone *ia= (phone*)a;
  phone *ib= (phone*)b;
  return strcmp(ia->name,ib->name);
}

int compareName(const void *a,const void *b)
{
  phone *ia= (phone*)a;
  phone *ib= (phone*)b;
  char s1[40];
  char s2[40];
  strcpy(s1,ia->name);
  strcpy(s2,ib->name);
  char buff1[40];
  char buff2[40];
  int i = strlen(s1);
  int j = strlen(s2);
  int check = 0;
  while(i >= 0 && j >= 0 && check == 0) {
    while(s1[i] != ' ' && i >= 0)
      i -= 1;
    while(s2[j] != ' ' && j >= 0)
      j -= 1;
    strncpy(buff1, s1 + i + 1, strlen(s1)-i+1);
    strncpy(buff2, s2 + j + 1, strlen(s2)-j+1);
    check = strcmp(buff1, buff2);
    if(check > 0) return 1;
    else if(check < 0) return -1;
    i--;
    j--;
  }
  if(i >= 0) return 1;
  if(j >= 0) return -1;
  return 0;   
}

int main(int argc,char* argv[]) {
  if (argc!=2) {
    printf("Wrong number of input\n");
    return 0;
  }
  FILE *fp;
  phone *phonearr;
  int i,irc,n=10;
  int reval=SUCCESS;
  phonearr=(phone*)malloc(n*sizeof(phone));
  if ((fp=fopen(argv[1],"r"))==NULL) {
    printf("Cannot open %s file\n",argv[1]);
    reval=FAIL;
  }
  printf("Original list: \n");
  for (i=0;i<n;i++) {
    fscanf(fp,"%[^\t]%*c %[^\n]%*c",phonearr[i].name,phonearr[i].tel);__fpurge(stdin);
    printf("%s-%s\n",phonearr[i].name,phonearr[i].tel);
  }
  fclose(fp);
  printf("________________________\n\n");
  qsort(phonearr,n,sizeof(phone),compareName);
  printf("Sorted list: \n");
  for (i=0;i<n;i++) {
    printf("%s-%s\n",phonearr[i].name,phonearr[i].tel);
  }
  free(phonearr);
}
