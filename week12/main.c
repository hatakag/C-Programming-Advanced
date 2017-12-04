#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_compress.h"
#include "graph.h"
#include "priority_queue.h"

int main() {
  char s[]="aaaabbbcc";
  HuffmanTree tree=makeHuffman(s,strlen(s));
  Coding huffmanTable[256];
  return 0;
}
