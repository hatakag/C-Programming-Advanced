#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jval.h"
#include "jrb.h"

enum{SUCCESS,FAIL};

typedef struct {
  char domain[100];
  char ip[15];
}dns;

//FUNCTION

void addEntry(JRB book,char* key,char* value) {
  JRB node=jrb_find_str(book,key);
  if (!node) {// if not exist insert new
    char *s;
    s=(char*)malloc(strlen(value)*sizeof(char));
    strcpy(s,value);
    jrb_insert_str(book,strdup(key),new_jval_s(s));// ip - domain
  }
  else {
    printf("Domain name and IP already exist!!!\n");
  }
  //(node->val).l=value; //overwrite if already exists
}

void printBook(JRB book) {
  if (jrb_empty(book)) printf("0 domain name and IP\n"); //if empty
  else {
    JRB node;
    jrb_traverse(node,book) {
      printf("%s : %s\n",jval_s(node->val),jval_s(node->key));
    }
  }
}

void freeBook(JRB book) {
  if (!jrb_empty(book)) {
    JRB node;
    jrb_traverse(node,book) {
      free((node->key).s);
      //free((node->val).s);
    }
  }
  jrb_free_tree(book);
}

int readBook(JRB book,FILE *fp) {
  int i,n;
  fscanf(fp,"%d%*c",&n);
  //printf("%d\n",n);
  if (n>=1000) {
    printf("Can not scan number\n");
    return 0;
  }
  dns *dnsarr;
  dnsarr=(dns*)malloc(n*sizeof(dns));
  for (i=0;i<n;i++) {
    fscanf(fp,"%[^\n]%*c %[^\n]%*c",dnsarr[i].domain,dnsarr[i].ip);//__fpurge(stdin);
    //printf("%s : %s\n",dnsarr[i].ip,dnsarr[i].domain);
    addEntry(book,dnsarr[i].ip,dnsarr[i].domain);
  }
  free(dnsarr);
  fclose(fp);
  return n;
}
/*
void writeBook(JRB book,FILE *fp1) {
  if (jrb_empty(book)) {}//fprintf(fp1,"0 domain name and IP\n"); //if empty
  else {
    fprintf(fp1,"");
    JRB node;
    jrb_traverse(node,book) {
      fprintf(fp1,"%s\n%s\n",jval_s(node->val),jval_s(node->key));
    }
  }
  fclose(fp1);
  }*/
//

int main(int argc, char* argv[]) {
  if (argc!=2) {
    printf("Wrong number of input\n");
    return 0;
  }
  int reval=SUCCESS;

  FILE *fp;
  if ((fp=fopen(argv[1],"r"))==NULL) {
    printf("Cannot open file %s\n",argv[1]);
    reval=FAIL;
  }
  
  //red black tree
  JRB book=make_jrb();

  
  //MENU 
  char menu[5][40]={"Read file and Display","Add","Find IP","Find domain name","Quit"};
  int choice,mark=0;
  int N;
  do {
    choice=0;
    printf("\n=====DNS=====\n");
    printf("\n _____MENU_____\n");
    int i;
    for (i=0;i<5;i++) 
      printf("%d.%s\n",i+1,menu[i]);
    printf("Select: ");scanf("%d",&choice);__fpurge(stdin);
    switch (choice) {
    case 1: 
      {
	if (mark==1) {
	  printf("Already read file\n");
	  printBook(book);
	}
	else {
	  // read from file to btree
	  N=readBook(book,fp);
	  if (N==0) mark=0;
	  else mark=1;
	  printBook(book);
	}
	break;
      }
    case 2:
      {
	if (mark==0) printf("Read file first\n");
	else {
	  char domain[100];
	  char ip[15];
	  printf("Domain: ");scanf("%[^\n]s%*c",domain);__fpurge(stdin);
	  printf("IP: ");scanf("%[^\n]s%*c",ip);__fpurge(stdin);
	  addEntry(book,ip,domain);
	  //printBook(book);
	  N++;
	}
	break;
      }
    case 3:
      {
	if (mark==0) printf("Read file first\n");
	else {
	  if (jrb_empty(book)) printf("0 domain name and IP\n"); //if empty
	  else {
	    char ip[15];
	    printf("IP: ");scanf("%[^\n]s%*c",ip);__fpurge(stdin);
	    JRB node=jrb_find_str(book,ip);
	    if (!node) {
	      printf("Not found\n");
	    } else {
	      printf("%s : %s\n",jval_s(node->val),jval_s(node->key));
	    }
	  }
	}
	break;
      }
    case 4:
      {
	if (mark==0) printf("Read file first\n");
	else {
	  if (jrb_empty(book)) printf("0 domain name and IP\n"); //if empty
	  else {
	    int check=0;
	    char domain[100];
	    printf("Domain: ");scanf("%[^\n]s%*c",domain);__fpurge(stdin);
	    JRB node;
	    jrb_traverse(node,book) {
	      if (strcmp(jval_s(node->val),domain)==0){
		printf("%s : %s\n",jval_s(node->val),jval_s(node->key));
		check=1;
	      }
	    }
	    if (check==0) printf("Not found\n");
	  }
	}
	break;
      }
    case 5:
      break;
    default: printf("Invalid choice\n");
      break;
    }
  }while(choice!=5);
  printf("\n___GOODBYE___\n");
      
  //write btree to file

  FILE *fp1;
  if ((fp1=fopen(argv[1],"w"))==NULL) {
    printf("Cannot open file %s\n",argv[1]);
    reval=FAIL;
  }
  if (jrb_empty(book)) {}//fprintf(fp1,"0 domain name and IP\n"); //if empty
  else {
    fprintf(fp1,"%d\n",N);
    JRB node;
    jrb_traverse(node,book) {
      fprintf(fp1,"%s\n%s\n",jval_s(node->val),jval_s(node->key));
    }
  }
  fclose(fp1);
  //writeBook(book,fp1);
  
  freeBook(book);  //jrb
  return reval;
}
