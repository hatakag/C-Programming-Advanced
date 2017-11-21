#ifndef DATA_COMPRESS_H
#define DATA_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jval.h"
#include "jrb.h"
#include "dllist.h"
#include "weighted_graph_jrb.h"

typedef struct {
   Graph graph;
   JRB root;
} HuffmanTree;

typedef struct {
  int size;
  unsigned char bits[2];
} Coding;

Coding huffmanTable[256];
HuffmanTree makeHuffman (char * buffer, int size);
void createHuffmanTable(HuffmanTree htree, Coding* htable);
void compress(char * buffer, int size, char* huffman, int* nbit);
void addHuffmanChar(char * ch, Coding* htable, char* huffman, int* nbit);

#endif
