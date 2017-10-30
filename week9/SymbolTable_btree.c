#include "SymbolTable_btree.h"

char *getEntry(BTA *book,char* key) {
  char *s=(char*)malloc(sizeof(char)*DATA_SIZE);
  int tmp,status;
  status=btsel(book,key,s,sizeof(char)*DATA_SIZE,&tmp);
  if (status!=0) {
    return NULL;
  }
  return s;
}

void addEntry(BTA *book,char* key,char* data) {
  int status;
  //bfndky(book,key,&val)!=0
  if (getEntry(book,key)==NULL) {          //if key do not exist insert new data
    status=btins(book,key,data,sizeof(char)*strlen(data));
    if (status!=0) printf("Error--addEntry:btins--Insert fail\n");
  } else {                                 //else update data
    status=btupd(book,key,data,sizeof(char)*strlen(data));
    if (status!=0) printf("Error--addEntry:btupd--Update fail\n");
  }
}

void searchEntry(BTA *book,char *key) {
  if (getEntry(book,key)==NULL) printf("Error--searchEntry:btsel--Not found\n");
  else {
    printf("Found\n");
    printf("%s----%s\n",key,getEntry(book,key));
  }
}

void deleteEntry(BTA *book,char *key) {
  int status;
  status=btdel(book,key);
  if (status!=0)
    printf("Error--deleteEntry:btdel--Delete fail\n");
  else printf("Deleted\n");
}

void modifyEntry(BTA *book,char *key,char *data) {
  if (getEntry(book,key)==NULL) printf("Error--modifyEntry:btsel--Not found\n");
  else {
    int status;
    status=btupd(book,key,data,sizeof(char)*strlen(data));
    if (status!=0) printf("Error--addEntry:btupd--Update fail\n");
    else printf("%s----%s\n",key,getEntry(book,key));
  }
}

void printPhone(BTA *book) { //print key and value in btree
  char name[40];
  char phone[20];
  int tmp;
  long j=0;
  btpos(book,ZSTART);
  while(btseln(book,name,phone,sizeof(char)*DATA_SIZE,&tmp)==0) {
    printf("%s----%s\n",name,phone);
    j++;
  }
  printf("n=%ld\n",j);
}

/*
void readPhone(BTA* book,FILE *fp) { //read from file to btree
  int i,n=MAX_PHONE;
  Phone *phonearr;
  phonearr=(Phone*)malloc(n*sizeof(Phone));
  for (i=0;i<n;i++) {
    fscanf(fp,"%[^\t]%*c %[^\n]%*c",phonearr[i].name,phonearr[i].phone);__fpurge(stdin);
    addEntry(book,phonearr[i].name,phonearr[i].phone);
  }
  free(phonearr);
}

void writePhone(BTA *book,FILE *fp) { //print key and value in btree
  char name[40];
  char phone[20];
  int tmp;
  long j=0;
  btpos(book,ZSTART);
  while(btseln(book,name,phone,sizeof(char)*DATA_SIZE,&tmp)==0) {
    fprintf(fp,"%s----%s\n",name,phone);
    j++;
  }
  fprintf(fp,"n=%ld\n",j);
}
*/
