// Note: JRB is defined as a pointer to a node
// JRB book=make_jrb();

void addEntry(JRB book,char* key,long value) {
  JRB node=jrb_find_str(book,key);
  if (!node) // if not exist insert new
    jrb_insert_str(book,strdup(key),new_jval_l(value));
  else 
    (node->val).l=value; //overwrite if already exists
}

void deleteEntry(JRB *book,char* key) {
  JRB node=jrb_find_str(*book,key);
  if (node) { //if exist -> delete
    free((node->key).s); // or jval_s(node->key)
    //free(&(node->val).l);
    jrb_delete_node(node);
  }
}

void modifyEntry(JRB book,char* key,long new_value) {
  JRB node=jrb_find_str(book,key);
  if (node) //if exist -> modify
    (node->val).l=new_value;
}

void printPhone(JRB book) {
  if (jrb_empty(book)) printf("No elements\n"); //if empty
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

/*
void readPhone(JRB book,FILE *fp) {
  int i,n=10;
  Phone *phonearr;
  phonearr=(Phone*)malloc(n*sizeof(Phone));
  for (i=0;i<n;i++) {
    fscanf(fp,"%[^\t]%*c %ld%*c",phonearr[i].name,&phonearr[i].phone);__fpurge(stdin);
    addEntry(book,phonearr[i].name,phonearr[i].phone);
  }
  free(phonearr);
  fclose(fp);
}
*/
/*
void writePhone(JRB book,FILE *fp1) {
  if (jrb_empty(book)) fprintf(fp1,"No elements\n"); //if empty
  else {
    JRB node;
    jrb_traverse(node,book) {
      fprintf(fp1,"%s----%ld\n",jval_s(node->key),jval_l(node->val));
    }
  }
  fclose(fp1);
}
*/
