#include "data_compress.h"

int compare1(Jval a,Jval b) {
  if (jval_i(a)<jval_i(b)) return -1;
  else return 1;
}

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
  jrb_traverse(tmp,stats) { //all char with feq
    // add vertex key:feq & val:char
    addVertex(tree.graph,jval_i(tmp->val),jval_i(tmp->key));
    // add edge to new vertex -> pointer to vertex
    JRB tree1=make_jrb();
    jrb_insert_gen(tree.graph.edges,tmp->val,new_jval_v(tree1),compare1);
    // tree1 have 1 node with key:char
    jrb_insert_gen(tree1,tmp->key,new_jval_d(0),compare1);
    // add to queue with key:feq & val:pointer to vertex
    priority_enqueue(tree.root,jval_i(tmp->val),tree1);
  }
  
  //while (!jrb_empty(tree.root)) { //not empty queue
  do {
    int feq1,feq2,feq3;
    JRB tree1,tree2,tree3;
    // dequeue 2 node with smallest key(feq)
    priority_extract_min(tree.root,&feq1,tree1);
    priority_extract_min(tree.root,&feq2,tree2);
    // make new vertex in graph with key = sum of 2 smallest key and direct to 2 vertices 
    feq3=feq1+feq2;
    printf("%d %d %d\n",feq1,feq2,feq3);
    addVertex(tree.graph,feq3,feq1);
    jrb_insert_gen(tree.graph.edges,new_jval_i(feq3),new_jval_v(tree3),compare1); // add tree3 -> pointer
    addEdge(tree.graph,feq3,feq1,0); //add left tree
    addEdge(tree.graph,feq3,feq2,1); //add right tree
    // enqueue new node key:feq3 & val:pointer to new vertex(tree3)
    priority_enqueue(tree.root,feq3,tree3);
  } while (jrb_first(tree.root)!=jrb_last(tree.root)); //only one node left
  
  return tree;
}



void createHuffmanTable(HuffmanTree htree, Coding* htable) {
  int i;
  for (i=0;i<256;i++) {
    htable[i].size=0;
    htable[i].bits[0]=0;
    htable[i].bits[1]=0;
  }
  JRB root=jrb_first(htree.root);
  JRB tree=(JRB)jval_v(root->val);
  JRB node;
  /*
  jrb_traverse(node,tree) {
    x=(x<<1)|((unsigned char)jval_d(node->val));
    node->key
    
    
    }
  */
}
void compress(char * buffer, int size, char* huffman, int* nbit) {
}
void addHuffmanChar(char * ch, Coding* htable, char* huffman, int* nbit) {
}
