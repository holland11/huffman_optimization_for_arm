#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node_t {
	u_int8_t letter;
	int freq_sum;
	struct Node_t* left;
	struct Node_t* right;
} Node;

int cmp_nodes(const void* a, const void* b);

Node** createArrayOfNodes(int* freq, int length);

Node* createTree(Node** nodes, int length);

#endif