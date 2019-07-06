#ifndef _HUFFMAN_DEBUG_H_
#define _HUFFMAN_DEBUG_H_

#include <stdio.h>
#include <stdlib.h>

#include "huffman_tree.h"
#include "huffman_utils.h"

#define COUNT 8

// https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 
  
  
typedef struct ArrayNode_t {
	u_int8_t letter, nbits;
	u_int8_t left, right;
} ArrayNode;

void buildStaticArrays();
  
void printDictionary(HuffCode huffcodes[], int length);

void findThirdLevelNodes(Node* node, Node** subtrees, int depth, int* index);

int analyzeTree(Node* node, int depth, int* count);

void traverseSubTrees(Node** subtrees, int* index);
  
void printNodes(Node** nodes, int length, int skip);

void print32binary(u_int32_t bin);

void print64binary(u_int64_t bin);

// Function to print binary tree in 2D 
// It does reverse inorder traversal 
// from https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void print2DUtil(Node *root, int space);
  
// Wrapper over print2DUtil() 
void print2D(Node *root);

void printHuffCodes(HuffCode huffcodes[], int length);

#endif