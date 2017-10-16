#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymbolTable.h"

// MAKE PHONE
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

int main() {
  SymbolTable phoneBook=createSymbolTable(makePhone,comparePhone);
  long number=123456789;
  char name[]="Bui Cong Thanh";
  long number1=987654321;
  char name1[]="Bui Cong Thanh";
  long number2=134354867;
  char name2[]="Thanh Cong Bui";
  long number3=354487964;
  char name3[]="Nguyen Van Hai";
  addEntry(name,&number,&phoneBook);
  Entry *thanh4=getEntry(name,phoneBook);
  printf("%s----%ld----%d----%d\n",(char*)(thanh4->key),*(long*)(thanh4->value),phoneBook.total,phoneBook.size);
  
  addEntry(name1,&number1,&phoneBook);
  Entry *thanh=getEntry(name,phoneBook);
  //int i=0;
  //while (i<2) {
    printf("%s----%ld----%d----%d\n",(char*)(thanh->key),*(long*)(thanh->value),phoneBook.total,phoneBook.size);
    // i++;
    //}
  addEntry(name2,&number2,&phoneBook);
  Entry *thanh2=getEntry(name2,phoneBook);
  printf("%s----%ld----%d----%d\n",(char*)(thanh2->key),*(long*)(thanh2->value),phoneBook.total,phoneBook.size);
  addEntry(name3,&number3,&phoneBook);
  Entry *thanh3=getEntry(name3,phoneBook);
  printf("%s----%ld----%d----%d\n",(char*)(thanh3->key),*(long*)(thanh3->value),phoneBook.total,phoneBook.size);
  printf("\n\n");
  printPhone(phoneBook);
  dropSymbolTable(&phoneBook);
  return 0;
}

