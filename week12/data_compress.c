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
    } //end if else
  }// end for
  
  return stats;
}

HuffmanTree makeHuffman (char* buffer, int size) {
  HuffmanTree tree;
  tree.graph=createGraph();
  tree.root=priority_make_queue();
  JRB stats=makeStatsTree(buffer,size);
  while () {
    
  }
}

void createHuffmanTable(HuffmanTree htree, Coding* htable) {
}
void compress(char * buffer, int size, char* huffman, int* nbit) {
}
void addHuffmanChar(char * ch, Coding* htable, char* huffman, int* nbit) {
}
