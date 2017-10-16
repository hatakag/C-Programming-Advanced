#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#define DATA_SIZE 20 
#define MAX_PHONE 10

enum{SUCCESS,FAIL};

// MAKE PHONE

typedef struct {
  char name[40];
  char phone[20];
}Phone;

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

int main(int argc,char* argv[]) {
  if (argc!=4) {
    printf("Wrong number of input\n");
    return 0;
  }
  int reval=SUCCESS;
  
  // Open file
  FILE * fp;
  if ((fp=fopen(argv[2],"r"))==NULL) {
    printf("Cannot open %s file\n",argv[1]);
    reval=FAIL;
  }
  FILE * fp1;
  if ((fp1=fopen(argv[3],"w"))==NULL) {
    printf("Cannot open %s file\n",argv[2]);
    reval=FAIL;
  }
  
  // btree
  BTA *book;
  btinit();
  if ((book=btopn(argv[1],0,0))!=NULL) {  // if file exists open B tree file
    btdups(book,FALSE);
    printf("Open file successfully\n");
  } else if ((book=btcrt(argv[1],0,0))!=NULL) { //else create file
    btdups(book,FALSE);
  } else {
    printf("Can't open file %s\n",argv[1]);
    return 0;
  }
  
  // read from file to btree
  readPhone(book,fp);
  fclose(fp);
  
  //MENU
  char menu[6][40]={"Add phone number","Find phone number","Delete phone number","Modify phone number","Print phone book","Quit"};
  int choice;
  do {
    choice=0;
    printf("\n====PHONEBOOK====\n");
    printf("\n _____MENU_____\n");
    int i;
    for (i=0;i<6;i++) 
      printf("%d.%s\n",i+1,menu[i]);
    printf("Select: ");scanf("%d",&choice);__fpurge(stdin);
    switch (choice) {
    case 1: 
      {
	char name[40];
	char phone[20];
	printf("Name: ");scanf("%[^\n]%*c",name);__fpurge(stdin);
	printf("Phone number: ");scanf("%[^\n]%*c",phone);__fpurge(stdin);
	addEntry(book,name,phone);
	break;
      }
    case 2:
      {
	char name[40];
	printf("Name: ");scanf("%[^\n]%*c",name);__fpurge(stdin);
	searchEntry(book,name);
	break;
      }
    case 3:
      {
	char name[40];
	printf("Name: ");scanf("%[^\n]%*c",name);__fpurge(stdin);
	deleteEntry(book,name);
	break;
      }
    case 4:
      {
	char name[40];
	char phone[20];
	printf("Name: ");scanf("%[^\n]%*c",name);__fpurge(stdin);
	printf("Phone number: ");scanf("%[^\n]%*c",phone);__fpurge(stdin);
	modifyEntry(book,name,phone);
	break;
      }
    case 5:
      {
	printPhone(book);
	break;
      }
    case 6:
      break;
    default: printf("Invalid choice\n");
      break;
    }
  }while(choice!=6);
  printf("\n___GOODBYE___\n");

  //write btree to file
  writePhone(book,fp1);
  fclose(fp1);
  
  btcls(book);
  return reval;
}

