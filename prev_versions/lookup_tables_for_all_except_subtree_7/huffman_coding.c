#include "huffman_coding.h"


void getBitStrings(HuffCode bit_strings[], Node* root, int depth, int bit_string) {
	
	if (root->left == NULL && root->right == NULL) {
		// found leaf node
		int index = (int)root->letter;
		bit_strings[index] = (HuffCode){depth, bit_string};
		//free(root); // done with the node so we can free the memeory
		return;
	}
	
	if (root->left != NULL)
		getBitStrings(bit_strings, root->left, depth+1, bit_string << 1);
	if (root->right != NULL)
		getBitStrings(bit_strings, root->right, depth+1, (bit_string << 1) + 1);
	
	//free(root); // done with the node so we can free the memory
	return;
}

void write32(FILE* f, u_int32_t bin) {
	// writes 32 bit int in native endian of the machine
	fwrite(&bin, sizeof(u_int32_t), 1, f);
	/*
	// writes 32 bit int in big endian order
	int i;
	for (i=3; i>=0; i--) {
		u_int8_t temp = bin >> i*8;
		fwrite(&temp, sizeof(u_int8_t), 1, f);
	}
	*/
}

void pack_bits(HuffCode* h, u_int32_t* bits_packed, u_int32_t* bin, FILE* f_out) {
	u_int32_t temp;
	if (*bits_packed + h->len <= 32) {
		// can pack these bits without overflow
		*bin = *bin << h->len; // shift the container to make room for the new bits
		*bin = *bin | h->code; // add the new bits by ORing them
		*bits_packed += h->len;
		if (*bits_packed == 32) {
			write32(f_out, *bin);
			*bits_packed = 0;
			*bin = 0;
		}
	} else {
		// there will be overflow to add to the next container
		temp = 32-*bits_packed;
		*bits_packed = h->len - temp;
		*bin = *bin << temp;
		temp = h->code >> *bits_packed; // right shift the bit code to trim the overflow
		*bin = *bin | temp;
		write32(f_out, *bin);
		temp = 32 - *bits_packed;
		*bin = (h->code << temp) >> temp; // left shift to trim the non-overflow bits then right shift to put the overflow bits back in place
	}
}

void encode(FILE* f_out, FILE* f_in, HuffCode dict[]) {
	u_int32_t i, temp, bits_packed=0, bin=0;
	HuffCode h;
	int c;
	while ((c = fgetc(f_in)) != EOF) {
		// read the input file 1 character at a time
		// might be better to read the entire file into a char array?
		h = dict[c];
		pack_bits(&h, &bits_packed, &bin, f_out);
	}
	
	h = dict[3]; // end of text character so the decoder knows when it hits the end
	pack_bits(&h, &bits_packed, &bin, f_out);
	
	if (bits_packed != 0) {
		// read all of the input, but haven't written the final binary values
		temp = 32-bits_packed;
		bin = bin << temp;
		write32(f_out, bin);
	}
}

int fillBuffer(u_int64_t *buffer, FILE *f_in) {
	// read 32 bits from f_in to place into the 64 bit address
	return fread(buffer, sizeof(u_int32_t), 1, f_in);
}

int readNBits(u_int8_t n, u_int8_t *bits_left_in_buffer, u_int64_t *buffer, FILE* f_in) {
	if (*bits_left_in_buffer <= n) {
		u_int64_t temp = *buffer << 32; // store these bits to put back into the buffer after reading next 32
		fillBuffer(buffer, f_in);
		*buffer = *buffer | temp;
		*bits_left_in_buffer += 32;
	}
	u_int32_t result = *buffer >> (*bits_left_in_buffer - n);
	*buffer = *buffer << (32 + (32 - (*bits_left_in_buffer - n))); // chunks off the read bits. 5 bits left, want 2, lshift 32+29 times (32 + (32 - (bits_left - n))
	*buffer = *buffer >> (32 + (32 - (*bits_left_in_buffer - n))); // move the bits back to their previous position
	*bits_left_in_buffer -= n;
	return result;
}

void storeNBitsBack(u_int8_t n, u_int64_t bits, u_int64_t *buffer, u_int8_t *bits_left_in_buffer) {
	// we didn't consume all of the bits to get to our leaf node so we store the remaining ones back into the buffer
	u_int64_t save_bits = ((bits << (64 - n)) >> (64 - n)) << *bits_left_in_buffer;
	*buffer = *buffer | save_bits;
	*bits_left_in_buffer += n;
}

void decode(FILE* f_out, FILE* f_in, HuffNode tree[], u_int8_t* lookup_tables[]) {
	/*
	tree 0 has height 0 and 1 nodes
	tree 1 has height 1 and 3 nodes
	tree 2 has height 1 and 3 nodes
	tree 3 has height 12 and 39 nodes
	tree 4 has height 3 and 7 nodes
	tree 5 has height 3 and 7 nodes
	tree 6 has height 0 and 1 nodes
	tree 7 has height 25 and 187 nodes
	
	1. Take 3 bits
	2. Use 3 bits to index into array which is an array of pointers to arrays.
	3a. If index is 0 or 6, we use fprint tree[index] and go back to (1).
	3b. If index is 1 or 2, we take 1 bit and use that to index into the array from (2)
		which indexes us into tree for our char. Then back to (1).
	3c. If index is 4 or 5, we take 7 bits and use that to index into the array from (2). 
		We look at arr[index].nbits to know how many bits to consume/save. Then back to (1).
	3d. If index is 3, we take 12 bits and do same as (3c).
	3e. If index is 7, we start doing a normal decode until we hit a leaf then go back to (1).
	
	Use buffer with 64 bits in case we pull the next 32 bits but need to save some leftover bits.
	Need a 	function to fetch the next 32 bits and put into buffer
			function to retrieve n bits from the buffer (which can call the above function if more needed).
			function to 'save' bits by putting them back into the buffer
	*/
	HuffNode node;
	u_int64_t buffer = 0;
	u_int32_t index = 0, table_index = 0;
	u_int8_t bits_left_in_buffer = 0;
	char c;
	int j = 0;
	
	// each iteration is one char
	// we break when we see int(c) == 3 (EOF)
	while (1) {
		// The quickbro n foes jumps oeeidha feznti zi ws ,ileee
		index = readNBits(3, &bits_left_in_buffer, &buffer, f_in); // this is index into subtree from root
		if (index == 0 || index == 6) {
			// subtree height 0 so we know we are at a leaf node already
			node = tree[index];
			c = (char)node.letter;
		} else if (index == 1 || index == 2) {
			// subtree height 1 so we need to take 1 bit
			table_index = readNBits(1, &bits_left_in_buffer, &buffer, f_in);
			node = tree[lookup_tables[index][table_index]];
			c = (char)node.letter;
		} else if (index == 4 || index == 5) {
			// subtree height 3 so we need to take 3 bits and maybe save some back to buffer after
			table_index = readNBits(3, &bits_left_in_buffer, &buffer, f_in);
			node = tree[lookup_tables[index][table_index]];
			c = (char)node.letter;
			if (node.nbits < 6) storeNBitsBack(6-node.nbits, (u_int64_t)table_index, &buffer, &bits_left_in_buffer);
		} else if (index == 3) {
			// subtree height 12 so we need to take 12 bits and maybe save some back to buffer after
			table_index = readNBits(12, &bits_left_in_buffer, &buffer, f_in);
			node = tree[lookup_tables[index][table_index]];
			c = (char)node.letter;
			if (node.nbits < 15) storeNBitsBack(15-node.nbits, (u_int64_t)table_index, &buffer, &bits_left_in_buffer);
		} else {
			// height 25 subtree so we have to walk 1 bit at a time until reaching a leaf
			node = tree[index];
			while (1) {
				if (!node.left && !node.right) {
					c = (char)node.letter;
					break;
				} else {
					table_index = readNBits(1, &bits_left_in_buffer, &buffer, f_in);
					node = (table_index) ? tree[node.right] : tree[node.left]; // if bit is 1, go to right child, else go left
				}
			}
		}
		if (c == '\3') {
			break; // EOF char so we are done decoding
		} else {
			fprintf(f_out, "%c", c);
		}
	}
}
/*
void decode(FILE* f_out, FILE* f_in, HuffNode tree[]) {
	u_int32_t buffer, bit;
	int i;
	HuffNode* node = tree;
	u_int8_t need = 3, index = 0;
	
	while (fread(&buffer, sizeof(u_int32_t), 1, f_in) != 0) {
		// buffer contains 32 bits that we will use to traverse the huffman tree
		for (i=0; i<32; i++) {
			bit = buffer >> 31; // shift to get only the leftmost bit
			buffer = buffer << 1; // left shift by 1 to discard the leftmost bit
			if (need) { // still trying to take first 3 bits of code
				need--;
				index = index << 1; // make room for new bit on code
				if (bit) index++;
				if (!need) { // have all 3 bits of code so we can choose subtree to traverse
					node = &tree[index];
				} else continue;
			}
			else {
				node = !bit ? &tree[node->left] : &tree[node->right]; // if bit is 0 go to left child. else go to right child.
			}
			if (node == NULL) {
				printf("error traversing tree\n");
				return;
			} else if (!node->left && !node->right) {
				// leaf node
				if (node->letter == '\3') return; // end of text character
				fprintf(f_out, "%c", (char)node->letter);
				need = 3; // need 3 bits for start of next code (to pick which subtree to traverse)
				index = 0;
			}
		}
	}
}*/