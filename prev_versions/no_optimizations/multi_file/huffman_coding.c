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
				node = !bit ? node+node->left : node+node->right; // if bit is 0 go to left child. else go to right child.
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
}