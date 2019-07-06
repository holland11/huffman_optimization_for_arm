#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stdio.h>
#include <stdlib.h>

#include "huffman_tree.h"

typedef struct HuffCode_t {
	u_int8_t len; // depth in the tree (root node is at depth 0)
	u_int32_t code; // if code is 7 (111), but len is 5, then the bit string will be 00111
} HuffCode;

typedef struct HuffNodeode_t {
	u_int8_t letter, left, right, nbits; 
} HuffNode;

void getBitStrings(HuffCode bit_strings[], Node* root, int depth, int bit_string);

void write32(FILE* f, u_int32_t bin);

void pack_bits(HuffCode* h, u_int32_t* bits_packed, u_int32_t* bin, FILE* f_out);

void encode(FILE* f_out, FILE* f_in, HuffCode dict[]);

void decode(FILE* f_out, FILE* f_in, HuffNode tree[], u_int8_t* lookup_tables[]);

#endif