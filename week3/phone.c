#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_SIZE 2
#define INCREMENTAL_SIZE 3

typedef struct {
  char name[80];
  long phone;
}PhoneEntry;

typedef struct {
  PhoneEntry *entries;
  int total;
  int size;
}PhoneBook;

PhoneBook createPhoneBook(){
  PhoneBook book;
  book.size=INITIAL_SIZE;
  book.total=0;
  book.entries=(PhoneEntry*)malloc(sizeof(PhoneEntry)*book.size);
  return book;
}

void dropPhoneBook(PhoneBook *book) {
  int i;
  //ko khai bao bang bo nho dong ko can free
  /*for (i=0;i<book->size;i++) { 
    free(book->entries[i].name);
    free(book->entries[i].phone);
    }*/
  free(book->entries);
}

PhoneEntry *getPhoneNumber(char* name,PhoneBook book) {
  int i=0;
  PhoneEntry *res=(PhoneEntry*)malloc(sizeof(PhoneEntry));
  while (i<book.total) {
    if (strcmp(book.entries[i].name,name)==0) {
      *res=book.entries[i];
      return res;
    }
    i++;
  }
  return NULL;
}

PhoneEntry makePhone(char* name,long number) {
  PhoneEntry res;
  strcpy(res.name,name);
  res.phone=number;
  return res;
}

void addPhoneNumber(char* name,long number,PhoneBook *book) {
  if (!getPhoneNumber(name,*book)) {
    if (book->total<book->size) { //(*book).total  <->  book->total
      book->entries[(book->total)++]=makePhone(name,number);
    }
    else {
      book->size+=INCREMENTAL_SIZE;
      book->entries=(PhoneEntry*)realloc(book->entries,sizeof(PhoneEntry)*(book->size)); //max size -> malloc new entries;
      book->entries[(book->total)++]=makePhone(name,number);
    }
  }
  else {
    int i=0;
    while (i<book->total) {
      if (strcmp(book->entries[i].name,name)==0) {
	/*free(book->entries[i].name);
	  free(book->entries[i].phone);*/
	book->entries[i]=makePhone(name,number);
      }
      i++;
    }
  }
}

void printPhone(PhoneBook book) {
  int i;
  for (i=0;i<book.total;i++) {
    printf("%s----%ld----%d----%d\n",book.entries[i].name,book.entries[i].phone,book.total,book.size);
  }
}

int main() {
  PhoneBook phoneBook=createPhoneBook();
  long number=123456789;
  char name[]="Bui Cong Thanh";
  long number1=987654321;
  char name1[]="Bui Cong Thanh";
  long number2=134354867;
  char name2[]="Thanh Cong Bui";
  long number3=354487964;
  char name3[]="Nguyen Van Hai";
  //
  addPhoneNumber(name,number,&phoneBook);
  PhoneEntry *thanh4=getPhoneNumber(name,phoneBook);
  printf("%s----%ld----%d----%d\n",thanh4->name,thanh4->phone,phoneBook.total,phoneBook.size);
  //
  addPhoneNumber(name1,number1,&phoneBook);
  PhoneEntry *thanh=getPhoneNumber(name1,phoneBook);
  printf("%s----%ld----%d----%d\n",thanh->name,thanh->phone,phoneBook.total,phoneBook.size);
  //
  addPhoneNumber(name2,number2,&phoneBook);
  PhoneEntry *thanh2=getPhoneNumber(name,phoneBook);
  printf("%s----%ld----%d----%d\n",thanh2->name,thanh2->phone,phoneBook.total,phoneBook.size);
  //
  addPhoneNumber(name3,number3,&phoneBook);
  PhoneEntry *thanh3=getPhoneNumber(name3,phoneBook);
  printf("%s----%ld----%d----%d\n",thanh3->name,thanh3->phone,phoneBook.total,phoneBook.size);
  //
  printf("\n\nPrint Phonebook:\n");
  printPhone(phoneBook);
  dropPhoneBook(&phoneBook);
  return 0;
}

