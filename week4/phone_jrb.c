#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "jval.h"

enum{SUCCESS,FAIL};

// MAKE PHONE

typedef struct {
  char name[40];
  long phone;
}Phone;

// Note: JRB is defined as a pointer to a node

void addEntry(JRB book,char* key,long value) {
  JRB node=jrb_find_str(book,key);
  if (!node)
    jrb_insert_str(book,strdup(key),new_jval_l(value));
  else 
    (node->val).l=value; //overwrite if already exists
}

void deleteEntry(JRB *book,char* key) {
  JRB node=jrb_find_str(*book,key);
  if (node) {
    free((node->key).s); // or jval_s(node->key)
    //free(&(node->val).l);
    jrb_delete_node(node);
  }
}

void modifyEntry(JRB book,char* key,long new_value) {
  JRB node=jrb_find_str(book,key);
  if (node) 
    (node->val).l=new_value;
}

void printPhone(JRB book) {
  if (jrb_empty(book)) printf("No elements\n");
  else {
    JRB node;
    jrb_traverse(node,book) {
      printf("%s----%ld\n",jval_s(node->key),jval_l(node->val));
    }
  }
}

void freePhone(JRB book) {
  if (!jrb_empty(book)) {
    JRB node;
    jrb_traverse(node,book) {
      free((node->key).s);
      //free(&(node->val).l);
    }
  }
  jrb_free_tree(book);
}

int main(int argc,char* argv[]) {
  if (argc!=3) {
    printf("Wrong number of input\n");
    return 0;
  }
  int reval=SUCCESS;

  // Open file
  FILE * fp;
  if ((fp=fopen(argv[1],"r"))==NULL) {
    printf("Cannot open %s file\n",argv[1]);
    reval=FAIL;
  }

  FILE * fp1;
  if ((fp1=fopen(argv[2],"w"))==NULL) {
    printf("Cannot open %s file\n",argv[2]);
    reval=FAIL;
  }

  JRB book=make_jrb();
  
  // Read file and Add to JRB
  int i,n=10;
  Phone *phonearr;
  phonearr=(Phone*)malloc(n*sizeof(Phone));
  for (i=0;i<n;i++) {
    fscanf(fp,"%[^\t]%*c %ld%*c",phonearr[i].name,&phonearr[i].phone);__fpurge(stdin);
    addEntry(book,phonearr[i].name,phonearr[i].phone);
  }
  free(phonearr);
  fclose(fp);
  
  int choice;
  do {
    choice=0;
    printf("\n_____MENU_____\n");
    printf("1.Add phone number\n");
    printf("2.Delete phone number\n");
    printf("3.Modify phone number\n");
    printf("4.Quit\n");
    printf("Select: ");scanf("%d",&choice);__fpurge(stdin);
    switch (choice) {
    case 1: 
      {
	char name[40];
	long phone;
	printf("Name: ");scanf("%[^\n]s%*c",name);__fpurge(stdin);
	printf("Phone number: ");scanf("%ld",&phone);__fpurge(stdin);
	addEntry(book,name,phone);
	break;
      }
    case 2:
      {
	char name[40];
	printf("Name: ");scanf("%[^\n]s%*c",name);__fpurge(stdin);
	deleteEntry(&book,name);
	break;
      }
    case 3:
      {
	char name[40];
	long phone;
	printf("Name: ");scanf("%[^\n]s%*c",name);__fpurge(stdin);
	printf("Phone number: ");scanf("%ld",&phone);__fpurge(stdin);
	modifyEntry(book,name,phone);
	break;
      }
    case 4: 
      break;
    default: printf("Invalid choice\n");
      break;
    }
  } while(choice!=4);
  
  // Print phonebook
  printf("\n");
  printPhone(book);
  printf("\n____GOODBYE____\n");

  // Write to find
  if (jrb_empty(book)) fprintf(fp1,"No elements\n");
  else {
    JRB node;
    jrb_traverse(node,book) {
      fprintf(fp1,"%s----%ld\n",jval_s(node->key),jval_l(node->val));
    }
  }
  fclose(fp1);

  //Free phone
  freePhone(book);
  return reval;
}
