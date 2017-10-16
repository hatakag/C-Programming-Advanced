#define INITIAL_SIZE 2
#define INCREMENTAL_SIZE 3

typedef struct {
  void *key;
  void *value;
}Entry;

typedef struct {
  Entry *entries;
  int size,total;
  Entry (*makeNode)(void*,void*);
  int (*compare)(void*,void*);
}SymbolTable;

SymbolTable createSymbolTable(Entry (*makeNode)(void*,void*),int (*compare)(void*,void*)) {
  SymbolTable book;
  book.size=INITIAL_SIZE;
  book.total=0;
  book.entries=(Entry*)malloc(sizeof(Entry)*(book.size));
  book.makeNode=makeNode;
  book.compare=compare;
  return book;
}

void dropSymbolTable(SymbolTable *tab) {
  int i;
  for (i=0;i<tab->size;i++) {
    free(tab->entries[i].key);
    free(tab->entries[i].value);
  }
  free(tab->entries);
}

Entry *getEntry(void *key,SymbolTable book) {
  int i=0;//j=0;
  Entry *res=(Entry*)malloc(sizeof(Entry));
  while (i<book.total) {
    if (book.compare(book.entries[i].key,key)==0) {
      //res=(Entry*)realloc(res,sizeof(Entry)*(j+1));
      *res=book.entries[i];//res[j++]
      return res;
    }
    i++;
  }
  return NULL;
}

void addEntry(void* key, void* value, SymbolTable *book){
  if (!getEntry(key,*book)) {
    if (book->total<book->size) { //(*book).total  <->  book->total
      book->entries[(book->total)++]=book->makeNode(key,value);
    }
    else {
      book->size+=INCREMENTAL_SIZE;
      book->entries=(Entry*)realloc(book->entries,sizeof(Entry)*(book->size)); //max size -> malloc new entries;
      book->entries[(book->total)++]=book->makeNode(key,value);
    }
  }
  else {
    int i=0;
    while (i<book->total) {
      if (book->compare(book->entries[i].key,key)==0) {
	free(book->entries[i].key);
	free(book->entries[i].value);
	book->entries[i]=book->makeNode(key,value);
      }
      i++;
    }
  }
}

