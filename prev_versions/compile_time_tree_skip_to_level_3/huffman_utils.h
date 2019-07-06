#ifndef _HUFFMAN_UTILS_H_
#define _HUFFMAN_UTILS_H_

#include "huffman_data.h"
#include "huffman_coding.h"

#define NALPHABET 128 // number of chars in our alphabet
#define NNODES 248 // number of nodes in the tree minus the first 2 levels

HuffCode* DICT;
HuffNode* TREE;

void build();

#endif