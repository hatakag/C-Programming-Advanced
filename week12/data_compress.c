/*--------------------CODE CUA THANH-----------------------*/

#include "data_compress.h"

JRB makeStatsTree(char *buffer, int size) {
// make jrb to count characters
  JRB stats;
  JRB found; // result of searching
  int val;
  int i;
  
  stats = make_jrb();
  
  for(i = 0; i < size; i++){
    found = jrb_find_int(stats, buffer[i]);
    if(!found){
      /* if not found, insert buffer[i] to
	 the tree with val as 1 */
      jrb_insert_int(stats, buffer[i],new_jval_i(1));
    }else{
      /* if found,
	 increase val of that node by 1 */
      val = jval_i(found->val) + 1;
      found->val =new_jval_i(val);
    } 
  }
  
  return stats;
}

HuffmanTree makeHuffman (char* buffer, int size) {
  HuffmanTree tree;
  tree.graph=createGraph();
  tree.root=priority_make_queue();
  JRB stats=makeStatsTree(buffer,size);
  JRB tmp;
  /*
  //enqueue in chronological order of char 
  jrb_traverse(tmp,stats) { //all char with feq
    // add new vertex to graph.vertices key:char & val:feq
    addVertex(tree.graph,jval_i(tmp->key),jval_i(tmp->val));
    // add new vertex to graph.edges -> pointer to vertex(node in graph.edges)
    // node->key = char 
    JRB tree1=make_jrb();
    JRB node=jrb_insert_int(tree.graph.edges,jval_i(tmp->key),new_jval_v(tree1));
    printf("%c %d\n",jval_i(node->key),jval_i(tmp->val));
    // add to queue with key:feq & val:pointer to vertex
    priority_enqueue(tree.root,jval_i(tmp->val),node);
  }
  */
  // enqueue in the first appearing(in buffer) order of char
  int j,mark[256];
  for (j=0;j<256;j++) mark[j]=0; 
  for (j=0;j<size;j++) {
    int ch=buffer[j];
    if (mark[ch]==0) {
      // add new vertex to graph.vertices key:char & val:feq
      tmp=jrb_find_int(stats,ch);
      addVertex(tree.graph,ch,jval_i(tmp->val));
      // add new vertex to graph.edges -> pointer to vertex(node in graph.edges)
      // node->key = char 
      JRB tree1=make_jrb();
      JRB node=jrb_insert_int(tree.graph.edges,ch,new_jval_v(tree1));
      //printf("%c %c %d\n",ch,jval_i(node->key),jval_i(tmp->val));
      // add to queue with key:feq & val:pointer to vertex
      priority_enqueue(tree.root,jval_i(tmp->val),node);
      mark[ch]=1;
    }
  }
  
  /*
  //test queue order 
  jrb_traverse(tmp,tree.root) {
    printf("%d %c\n",jval_i(tmp->key),((JRB)jval_v(tmp->val))->key);
  }
  */
  
  int i=-1;
  //while (!jrb_empty(tree.root)) { //not empty queue
  do {
    int feq1,feq2,feq3;
    JRB node1,node2,tree3=make_jrb();
    //dequeue 2 node with smallest key(in queue not in graph-> key:feq)
    priority_extract_min(tree.root,&feq1,&node1);
    priority_extract_min(tree.root,&feq2,&node2);
    // make new vertex in graph with val(feq) = sum of 2 smallest val and directs to those 2 vertices 
    //key=-1,-2,...different from 0 to 255 (all char)
    feq3=feq1+feq2;
    //printf("%d %d %d\n",feq1,feq2,feq3);
    addVertex(tree.graph,i,feq3);
    // add node3 -> pointer
    JRB node3=jrb_insert_int(tree.graph.edges,i,new_jval_v(tree3));
    addEdge(tree.graph,i,jval_i(node1->key),0); //add left tree
    addEdge(tree.graph,i,jval_i(node2->key),1); //add right tree
    //printf("%c %c %d\n",jval_i(node1->key),jval_i(node2->key),i);
    i--;
    // enqueue new node key:feq3 & val:pointer to new vertex(node3)
    priority_enqueue(tree.root,feq3,node3);
  } while (jrb_first(tree.root)!=jrb_last(tree.root)); //only one node left
  
  return tree;
}


/* unsigned int not unsigned char because
   unsigned char is only from 0 to 255 (00000000->11111111)
   unsigned int is from 0 to super large number
   -> so if code has more than 8 bits can't use unsigned char
   -> array of 2 unsigned char (that why Coding has bits[2]) -> max 16 bits 
   size is the number of bits of code representing for char 
   ( 10 != 0010 both have bits=2 but size1=2 size2=4)
*/
unsigned int encodeChar(Graph g,int root,int ch,int *size) { 
  if (hasEdge(g,root,ch)!=0) {//has edge from root to ch
    (*size)++;
    //printf("%d %f\n",root,getEdgeValue(g,root,ch));
    return (unsigned int)getEdgeValue(g,root,ch);
  }
  else {
    int indegree_v[1];
    if (indegree(g,ch,indegree_v)==1) { 
      (*size)++;
      //printf("%d %f\n",indegree_v[0],getEdgeValue(g,indegree_v[0],ch));
      return ((unsigned int)(getEdgeValue(g,indegree_v[0],ch)) | (encodeChar(g,root,indegree_v[0],size)<<1));
    }
    else {
      printf("Error: more than 1 indegree\n");
      return 0;
    }
  }
}

void createHuffmanTable(HuffmanTree htree, Coding* htable) {
  int i;
  for (i=0;i<256;i++) {
    htable[i].size=0;
    htable[i].bits[0]=0;
    htable[i].bits[1]=0;
  }
  
  JRB root=jrb_first(htree.root); //only node(root) left in queue 
  JRB node=(JRB)jval_v(root->val); //root->val is node root in tree(graph.edges)
  int root_key=jval_i(node->key);//node root
  
  Graph g=htree.graph;
  JRB tmp;
  int ch;
  jrb_traverse(tmp,g.vertices) {
    ch=jval_i(tmp->key); //key:char
    if (ch>=0) {
      unsigned int code=encodeChar(g,root_key,ch,&htable[ch].size);
      if (code<=255) //max is 8 bits 1 (11111111)
	htable[ch].bits[0]=(unsigned char)(code);
      else { // need more than 8 bits
	htable[ch].bits[1]=(unsigned char)(code >> 8);
	htable[ch].bits[0]=(unsigned char)(code & 0xff); //ff(16)=11111111(2)
      }
      printf("%c %d %d %2d\t%s\n",ch,getVertex(g,ch),htable[ch].size,htable[ch].bits[0],getBits(htable[ch].bits[0],htable[ch].size));
    }
  }
}

char* getBits(unsigned char bits,int size) {
  int i;
  char *output;
  output=(char*)malloc(sizeof(char)*size);
  for(i=0;i<size;++i) {
    output[i] = ((bits>>(size-1-i))&1) + '0'; //+'0' to convert from int to char
  }
  //printf("%s ",output);
  return output;
}

void compress(char * buffer, int size, char* huffman, int* nbit) {
  int i;
  HuffmanTree tree=makeHuffman(buffer,size);
  Coding huffmanTable[256];
  createHuffmanTable(tree,huffmanTable);
  //char *s=strdup(buffer); //need if we declare char buffer[]="..."
  for (i=0;i<size;i++) {
    //printf("%c\n",s[i]);
    addHuffmanChar(buffer[i],huffmanTable,huffman,nbit);
  }
}

void addHuffmanChar(char ch, Coding * htable, char* huffman, int* nbit) {
  unsigned char bits0=htable[(int)ch].bits[0];
  unsigned char bits1=htable[(int)ch].bits[1];
  int size=htable[(int)ch].size;
  //printf(">%c %d %d %d\n",ch,size,bits0,bits1);
  if (size<=8) 
    {strcat(huffman,getBits(bits0,size));printf("%s ",getBits(bits0,size));}
  else {
    strcat(huffman,getBits(bits0,8));
    strcat(huffman,getBits(bits1,size-8));
  }
  (*nbit)+=size;
}
