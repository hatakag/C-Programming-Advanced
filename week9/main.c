#include <string.h>
#include <stdlib.h>
#include <string.h>
//#include "btree.h"
//#include "jval.h"
//#include "jrb.h"
#define 
#define


enum{SUCCESS,FAIL};

typedef struct {
  char ;
  char ;
};

//FUNCTION

int main(int argc, char* argv[]) {
  if (argc!=4) {
    printf("Wrong number of input\n");
    return 0;
  }
  int reval=SUCCESS;
  FILE *fp;
  if ((fp=fopen(argv[2],"r")==NULL)) {
    printf("Cannot open file %s\n",argv[2]);
    reval=FAIL;
  }
  FILE * fp1;
  if ((fp1=fopen(argv[3],"w"))==NULL) {
    printf("Cannot open %s file\n",argv[2]);
    reval=FAIL;
  }

  //red black tree
  //JRB book=make_jrb();
  
  //btree
  /*
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
  */
  
  // read from file to btree
  //readPhone(book,fp);
  //fclose(fp);

  //MENU 
  char menu[6][40]={"Add","Find","Delete","Modify","Print","Quit"};
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
	break;
      }
    case 2:
      {
	break;
      }
    case 3:
      {
	break;
      }
    case 4:
      {
	break;
      }
    case 5:
      {
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
  //writePhone(book,fp1);
  //fclose(fp1);
  //btcls(book);
  //freePhone(book);  //jrb
  return reval;
}
