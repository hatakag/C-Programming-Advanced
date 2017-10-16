#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymbolTable.h"

enum{SUCCESS,FAIL};

// MAKE PHONE

typedef struct {
  char name[40];
  long phone;
}Phone;

Entry makePhone(void* name,void* phone) {
  Entry res;
  res.key=strdup((char*)name);
  res.value=malloc(sizeof(long));
  memcpy(res.value,phone,sizeof(long));
  return res;
}

int comparePhone(void *key1,void *key2) {
  return strcmp((char*)key1,(char*)key2);
}

void printPhone(SymbolTable book) {
  int i;
  for (i=0;i<book.total;i++) {
    printf("%s----%ld----%d----%d\n",(char*)(book.entries[i].key),*(long*)(book.entries[i].value),book.total,book.size);
  }
}

int main(int argc,char* argv[]) {
  SymbolTable phoneBook=createSymbolTable(makePhone,comparePhone);
  if (argc!=2) {
    printf("Wrong number of input\n");
    return 0;
  }
  FILE * fp;
  Phone *phonearr;
  int i,n=10;
  int reval=SUCCESS;
  phonearr=(Phone*)malloc(n*sizeof(Phone));
  if ((fp=fopen(argv[1],"r"))==NULL) {
    printf("Cannot open %s file\n",argv[1]);
    reval=FAIL;
  }
  for (i=0;i<n;i++) {
    fscanf(fp,"%[^\t]%*c %ld%*c",phonearr[i].name,&phonearr[i].phone);__fpurge(stdin);
    //printf("%s-%ld\n",phonearr[i].name,phonearr[i].phone);
    addEntry(phonearr[i].name,&phonearr[i].phone,&phoneBook);
  }
  fclose(fp);
  free(phonearr);
  printf("Print Phonebook:\n");
  printPhone(phoneBook);
  char name[]="Bui Cong Thanh";
  long number=987654321;
  printf("\nAdd Entry:\n");
  addEntry(name,&number,&phoneBook);
  Entry *thanh=getEntry(name,phoneBook);
  printf("%s----%ld----%d----%d\n",(char*)(thanh->key),*(long*)(thanh->value),phoneBook.total,phoneBook.size);
  printf("\nNew Phoneook:\n");
  printPhone(phoneBook);
  dropSymbolTable(&phoneBook);
  return reval;
}
