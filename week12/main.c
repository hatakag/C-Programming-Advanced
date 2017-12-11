#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_compress.h"
#include "graph.h"
#include "priority_queue.h"

int main() {
  char s[26]="Eerie eyes seen near lake.";
  /*
  HuffmanTree tree=makeHuffman(s,strlen(s));
  Coding huffmanTable[256];
  createHuffmanTable(tree,huffmanTable);
  */
  char huffman[100]="";
  int nbit=0;
  printf("\n%s\n\n",s);
  compress(s,strlen(s),huffman,&nbit);
  //printf("\n%s\n",s);
  printf("\n\nHuffman buffer: %s\n",huffman);
  printf("Number of bits: %d\n",nbit);
  return 0;
}
