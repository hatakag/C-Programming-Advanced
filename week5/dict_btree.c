#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "btree.h"
//#include "getch_getche.h"
#include "soundex.h"
#include "complete.h"
#define KEY_SIZE 150
#define DATA_SIZE 150000
#define MAX_DICT 100000
#define LINE_SIZE 256

enum{SUCCESS,FAIL};

typedef struct {
  char word[KEY_SIZE];
  char mean[DATA_SIZE];
}Dict;

char *getWord(BTA *dict,char* key) {
  char *s=(char*)malloc(sizeof(char)*DATA_SIZE);
  int tmp,status;
  status=btsel(dict,key,s,sizeof(char)*DATA_SIZE,&tmp);
  if (status!=0) {
    return NULL;
  }
  return s;
}

void addWord(BTA *dict,char* key,char* data) {
  if (getWord(dict,key)==NULL) {
    int status;
    status=btins(dict,key,data,sizeof(char)*strlen(data));
    if (status!=0) printf("Error--addWord:btins--Insert fail\n");
  } else printf("That word is already defined!");
}

void searchWord(BTA *dict,BTA *soundexT,char *word_in) {
  if (getWord(dict,word_in)==NULL) {
    const char *sdx_in;
    init();
    sdx_in=soundex(word_in);
    int tmp;
    char word[KEY_SIZE], key[4];
    printf("Not found!\n-->Suggestion:\n");
    btpos(soundexT,ZSTART);
    while(btseln(soundexT,key,word,sizeof(char)*KEY_SIZE,&tmp)==0) {
      //printf("%s---%s---%s\n",sdx_in,key,word);
      if (strncmp(sdx_in,key,strlen(sdx_in))==0) 
	printf("%s\n",word);
    }
  }
  else {
    printf("Found\n");
    printf("%s : %s\n",word_in,getWord(dict,word_in));
  }
}

void deleteWord(BTA *dict,char *key) {
  int status;
  status=btdel(dict,key);
  if (status!=0)
    printf("Error--deleteWord:btdel--Delete word fail\n");
  else printf("Word deleted\n");
}

void printWord(BTA *dict) { //print key and value in btree
  char word[KEY_SIZE];
  char mean[DATA_SIZE];
  int tmp;
  long j=0;
  btpos(dict,ZSTART);
  while(btseln(dict,word,mean,sizeof(char)*DATA_SIZE,&tmp)==0) {
    printf("%s : %s\n",word,mean);
    j++;
  }
  printf("n=%ld\n",j);
}

// read file
void separateWordMean(char *word, char *mean, char *line) {
  /* format input for mean and word */
  mean[0] = '\0';
  /* strchr find char in str return position if found (char*) */ 
  char *p = strchr(line, '/');
  if (p != NULL) {
    strcpy(mean, p);
    *p = '\0';
    
    strcpy(word, line+1);
    // remove last space
    if (strlen(word) != 0)
      if (word[strlen(word) - 1] == ' ')
	word[strlen(word) - 1] = '\0';
  } else {
    //remove last enter
    strcpy(word, line+1);
    //remove last enter
    if (strlen(word) != 0)
      if (word[strlen(word) - 1] == '\n')
	word[strlen(word) - 1] = '\0';
  }
  
}


void readDict(BTA **root,FILE *fp) {  
  
  char word[KEY_SIZE];
  char mean[DATA_SIZE];
  char line[LINE_SIZE];
  
  //fseek(fp, 0, SEEK_SET);
  int count=0;
  // xu li phan dau file txt //
  while(1){
    fgets(line,LINE_SIZE,fp);
    //puts(line);
    //1. split line into word and mean 
    // strstr: find str2 trong str1 tra ve str1 neu tim thay 
    if(strstr(line, "@a") !=  NULL) {
      separateWordMean(word,mean,line);
      break;
    }
  }
  //2 . after that, append more line of mean, and repeat
  while(!feof(fp)){
    //if(count == 3) break;
    fgets(line,LINE_SIZE,fp);
    while(line[0] != '@') {
      if(feof(fp)) break;
      strcat(mean, line);
      fgets(line,LINE_SIZE,fp);
    }
    int result = btins(*root, word, mean, DATA_SIZE);
    if (result == 0) {
      count++;
      //printf("word: %s|\nmean: %s|\n",word, mean);
    }
    if(line[0] == '@') {
      separateWordMean(word,mean,line);	
    }		
  }
  printf("Word added into dictionary: %d\n", count);
  //fclose(fp);
}

void writeDict(BTA *dict,FILE *fp) { //print key and value in btree
  char word[KEY_SIZE];
  char mean[DATA_SIZE];
  int tmp;
  long j=0;
  btpos(dict,ZSTART);
  while(btseln(dict,word,mean,sizeof(char)*DATA_SIZE,&tmp)==0) {
    fprintf(fp,"%s : %s\n",word,mean);
    j++;
  }
  fprintf(fp,"n=%ld\n",j);
}
/*
void autocomplete(BTA *dict,char *word,int i,int max,int status) {
  char c;
  for(c=97;c<=122;c++) {
    word[i]=c;word[i+1]='\0';
    if (getWord(dict,word)!=NULL) {
      printf("\n%s\n",word);
      status=1;
      if (getchar()=='\n')
	printf("%s : %s\n",word,getWord(dict,word));
      break;
    }
  }
  if (status==0) {
    for(c=97;c<=122;c++) {
      if (i<max) {
	word[i]=c;word[i+1]='\0';
	//printf("\n%s\n",word);
	autocomplete(dict,word,i+1,max,status);
      }
    }
  }
}
*/
void readSoundex(BTA **soundexT,BTA* dict) {
  char word[KEY_SIZE],mean[DATA_SIZE];
  int tmp;
  const char* sdx;
  init();
  btpos(dict,ZSTART);
  while(btseln(dict,word,mean,sizeof(char)*DATA_SIZE,&tmp)==0) {
    sdx=soundex(word);
    btins(*soundexT,(char*)sdx,word,sizeof(char)*strlen(word));
  }
}

int main(int argc,char* argv[]) {
  if (argc!=5) {
    printf("Wrong number of input\n");
    return 0;
  }
  int reval=SUCCESS;
  
  // Open file
  FILE * fp;
  if ((fp=fopen(argv[3],"r"))==NULL) {
    printf("Cannot open file %s\n",argv[1]);
    reval=FAIL;
  }
  FILE * fp1;
  if ((fp1=fopen(argv[4],"w"))==NULL) {
    printf("Cannot open file %s\n",argv[2]);
    reval=FAIL;
  }
  
  // btree Dictionary
  BTA *dict;
  btinit();
  if ((dict=btopn(argv[1],0,0))!=NULL) {  // if file exists open B tree file
    btdups(dict,FALSE);
    printf("Open file successfully\n");
  } else if ((dict=btcrt(argv[1],0,0))!=NULL) { //else create file
    btdups(dict,FALSE);
  } else {
    printf("Can't open file %s\n",argv[1]);
    return 0;
  }

  // btree Soundex
  BTA *soundexT;
  btinit();
  if ((soundexT=btopn(argv[2],0,0))!=NULL) {  // if file exists open B tree file
    btdups(soundexT,TRUE);
    printf("Open file successfully\n");
  } else if ((soundexT=btcrt(argv[2],0,0))!=NULL) { //else create file
    btdups(soundexT,TRUE);
  } else {
    printf("Can't open file %s\n",argv[2]);
    return 0;
  }
  
  
  // read from file to btree
  readDict(&dict,fp);
  readSoundex(&soundexT,dict);
  fclose(fp);

  // var
  char word[KEY_SIZE];
  char mean[DATA_SIZE];
  char s[LINE_SIZE];
  char pri[]="Word : ";

  //MENU
  char menu[5][40]={"Add word","Search word","Delete word","Print dictionary","Quit"};
  int choice;
  do {
    choice=0;
    printf("\n====DICTIONARY====\n");
    printf("\n_______MENU_______\n");
    int i;
    for (i=0;i<5;i++) 
      printf("%d.%s\n",i+1,menu[i]);
    printf("Select: ");scanf("%d",&choice);__fpurge(stdin);
    switch (choice) {
    case 1: 
      {
	printf("Word: ");scanf("%[^\n]%*c",word);__fpurge(stdin);
	printf("Mean: ");scanf("%[^\n]%*c",mean);__fpurge(stdin);
	addWord(dict,word,mean);
	// add soundex
	const char* sdx;
	sdx=soundex(word);
	btins(soundexT,(char*)sdx,word,sizeof(char)*strlen(word));
	//
	break;
      }
    case 2:
      {
	write(STDOUT_FILENO,pri,strlen(pri));
	tab_complete(dict,s);
	strcpy(word,s);
	searchWord(dict,soundexT,word);
	break;
      }
    case 3:
      {
	write(STDOUT_FILENO,pri,strlen(pri));
	tab_complete(dict,s);
	strcpy(word,s);
	deleteWord(dict,word);
	// delete soundex
	/*
	int tmp;
	const char* sdx;
	sdx=soundex(word);
	int tmp1;char word1[100],s1[100];
	btpos(soundexT,ZSTART);
	while (btseln(soundexT,s1,word1,sizeof(char)*KEY_SIZE,&tmp1)==0) {
	  //printf("%s---%s\n",s1,word1);
	  if (strncmp(word,word1,strlen(word))==0 && strcmp((char*)sdx,s1)==0) {
	    int status;
	    status=btdel(soundexT,s1);
	    if (status!=0)
	    printf("Error--deleteWord:btdel--Delete soundex fail\n");
	      else printf("Soundex-word deleted\n");
	  }
	}
	*/
	//
	break;
      }
	  /*
    case 4:
      {
	char c;
	int i=0,status=0;
	printf("Word: ");
	do {
	  c=getche();
	  if (c=='\t') {
	    autocomplete(dict,word,i,2*i+1,status);
	  } else {
	    word[i]=c;word[i+1]='\0';i++;
	  }
	}while(c!='\n' && status==0);
	//searchWord(dict,word);
	break;
      }
    case 4:
      {
        char word_in[KEY_SIZE], word[KEY_SIZE], key[4];
	write(STDOUT_FILENO,pri,strlen(pri));
	tab_complete(dict,s);
	strcpy(word_in,s);
	const char *sdx_in;
	init();
	sdx_in=soundex(word_in);
	printf("%s\n",sdx_in);
	int tmp;
	printf("\nSuggestion\n\n");
	btpos(soundexT,ZSTART);
	while(btseln(soundexT,key,word,sizeof(char)*40,&tmp)==0) {
	  printf("%s---%s\n",sdx_in,key);
	  if (strcmp(sdx_in,key)==0) 
	    printf("%s : %s\n",word,getWord(dict,word));
	}
	break;
      }
	  */
    case 4:
      {
	printWord(dict);
	//printWord(soundexT);
	break;
      }
    case 5:
      break;
    default: printf("Invalid choice\n");
      break;
    }
  }while(choice!=5);
  printf("\n____GOODBYE____\n");

  //write btree to file
  writeDict(dict,fp1);
  fclose(fp1);
  
  btcls(dict);
  btcls(soundexT);
  return reval;
}
