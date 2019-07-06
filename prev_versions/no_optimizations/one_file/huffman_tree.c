#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 8
#define NALPHABET 128 // number of chars in our alphabet
#define MAXASCII 128 // the highest ascii character + 1 so that we can index into array using ascii code

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

typedef struct Node_t {
	char c;
	int freq_sum;
	struct Node_t* leftChild;
	struct Node_t* rightChild;
} Node;

typedef struct HuffCode_t {
	u_int32_t nbits; // depth in the tree (root node is at depth 0)
	u_int32_t num; // if num is 7 (111), but nbits is 5, then the bit string will be 00111
} HuffCode;

int cmp_nodes(const void* a, const void* b) {
	Node* node_a = *(Node**)a;
	Node* node_b = *(Node**)b;
	return node_a->freq_sum - node_b->freq_sum;
}

void printNodes(Node** nodes, int length, int skip) {
	int i;
	printf("[\n");
	for (i=skip; i<length; i++) {
		printf("%c: %d\n", nodes[i]->c, nodes[i]->freq_sum);
	}
	printf("]\n");
}

void print32binary(u_int32_t bin) {
	printf("bin: "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(bin>>24), BYTE_TO_BINARY(bin>>16), BYTE_TO_BINARY(bin>>8), BYTE_TO_BINARY(bin));
}

// Function to print binary tree in 2D 
// It does reverse inorder traversal 
// from https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void print2DUtil(Node *root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(root->rightChild, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->freq_sum); 
  
    // Process left child 
    print2DUtil(root->leftChild, space); 
} 
  
// Wrapper over print2DUtil() 
void print2D(Node *root) 
{ 
   // Pass initial space count as 0 
   print2DUtil(root, 0); 
} 

Node** createArrayOfNodes(int* freq, int length) {
	int i;
	Node** nodes = (Node**)malloc(sizeof(Node*)*length);
	for (i=0; i<length; i++) {
		Node* node = (Node*)malloc(sizeof(Node));
		node->c = (char)i;
		node->freq_sum = freq[i];
		node->leftChild = NULL;
		node->rightChild = NULL;
		nodes[i] = node;
	}
	qsort(nodes, length, sizeof(Node*), cmp_nodes);
	return nodes;
}

Node* createTree(Node** nodes, int length) {
	/*
	select 2 front items in array
	create new node from them
	find location in array where this new node should sit (sorted order)
	shift everything up to that point 1 spot to the left
	insert new node
	repeat until only 1 node remains and return that node (it is the root node)
	*/
	int i,j,k;
	for (i=0; i<length-1; i++) {
		Node* node_a = nodes[i];
		Node* node_b = nodes[i+1];
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->c = NULL;
		new_node->freq_sum = node_a->freq_sum + node_b->freq_sum;
		new_node->leftChild = node_a;
		new_node->rightChild = node_b;
		// find where new_node should go in the sorted array
		for (j=i+2; j<length; j++) {
			Node* node_c = nodes[j];
			if (new_node->freq_sum < node_c->freq_sum) {
				break;
			}
		}
		// new_node needs to go into index j-1
		// now we need to shift each element between i+2 and j-1 (inclusive) 1 element to the left
		// we don't have to worry about overwriting node_a and node_b in the array since they are no pointed to by new_node
		for (k=i+2; k<j; k++) {
			nodes[k-1] = nodes[k];
		}
		nodes[j-1] = new_node;
	}
	return nodes[length-1];
}

void getBitStrings(HuffCode bit_strings[], Node* root, int depth, int bit_string) {
	
	if (root->c != NULL) {
		// found leaf node
		int index = (int)root->c;
		bit_strings[index] = (HuffCode){depth, bit_string};
		free(root); // done with the node so we can free the memeory
		return;
	}
	
	if (root->leftChild != NULL)
		getBitStrings(bit_strings, root->leftChild, depth+1, bit_string << 1);
	if (root->rightChild != NULL)
		getBitStrings(bit_strings, root->rightChild, depth+1, (bit_string << 1) + 1);
	
	free(root); // done with the node so we can free the memory
	return;
}

void printHuffCodes(HuffCode huffcodes[], int length) {
	int i,j;
	for (i=0; i<length; i++) {
		HuffCode huffcode = huffcodes[i];
		printf("%d %d %d ", i, huffcode.nbits, huffcode.num);
		// nbits = 5, num = 5 (00000101) -> 00101
		for (j=huffcode.nbits-1; j>=0; j--) {
			int temp = (huffcode.num >> j) & 1;
			printf("%d",temp);
		}
		printf("\n");
	}
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
	if (*bits_packed + h->nbits <= 32) {
		// can pack these bits without overflow
		*bin = *bin << h->nbits; // shift the container to make room for the new bits
		*bin = *bin | h->num; // add the new bits by ORing them
		*bits_packed += h->nbits;
		if (*bits_packed == 32) {
			write32(f_out, *bin);
			*bits_packed = 0;
			*bin = 0;
		}
	} else {
		// there will be overflow to add to the next container
		temp = 32-*bits_packed;
		*bits_packed = h->nbits - temp;
		*bin = *bin << temp;
		temp = h->num >> *bits_packed; // right shift the bit code to trim the overflow
		*bin = *bin | temp;
		write32(f_out, *bin);
		temp = 32 - *bits_packed;
		*bin = (h->num << temp) >> temp; // left shift to trim the non-overflow bits then right shift to put the overflow bits back in place
	}
}

void encode(FILE* f_out, FILE* f_in, HuffCode huffcodes[]) {
	u_int32_t i, temp, bits_packed=0, bin=0;
	HuffCode h;
	int c;
	while ((c = fgetc(f_in)) != EOF) {
		// read the input file 1 character at a time
		// might be better to read the entire file into a char array?
		h = huffcodes[c];
		pack_bits(&h, &bits_packed, &bin, f_out);
	}
	
	h = huffcodes[3]; // end of text character so the decoder knows when it hits the end
	pack_bits(&h, &bits_packed, &bin, f_out);
	
	if (bits_packed != 0) {
		// read all of the input, but haven't written the final binary values
		temp = 32-bits_packed;
		bin = bin << temp;
		write32(f_out, bin);
	}
}

void decode(FILE* f_out, FILE* f_in, Node* root) {
	u_int32_t buffer;
	int i;
	Node* node = root;
	
	while (fread(&buffer, sizeof(u_int32_t), 1, f_in) != 0) {
		// buffer contains 32 bits that we will use to traverse the huffman tree
		for (i=0; i<32; i++) {
			u_int32_t bit = buffer >> 31; // shift to get only the leftmost bit 
			buffer = buffer << 1; // left shift by 1 to discard the leftmost bit
			node = !bit ? node->leftChild : node->rightChild; // if bit is 0 go to left child. else go to right child.
			if (node == NULL) {
				printf("error traversing tree\n");
				return;
			} else if (node->leftChild == NULL && node->rightChild == NULL) {
				// leaf node
				if (node->c == '\3') return; // end of text character
				fprintf(f_out, "%c", node->c);
				node = root;
			}
		}
	}
}

int handleArgs(int argc, char* argv[], char** inFile, char** outFile) {
	char* arg_msg = "Program arguments incorrect.\n./a.out phase [input_file, [output_file]]\nex: ./a.out encode input.txt output.bin\n";
	char* example_args = "";
	if (argc < 3) {
		printf("%s\n", arg_msg);
		return -1;
	}
	
	*inFile = argv[2];
	if (argc == 3) {
		*outFile = NULL;
	} else if (argc == 4) {
		*outFile = argv[3];
	} else {
		printf("%s\n", arg_msg);
		return -1;
	}
	
	if (!strcmp(argv[1], "encode")) {
		printf("output file not specified so using output.bin\n");
		return 0;
	} else if (!strcmp(argv[1], "decode")) {
		printf("output file not specified so using output.txt\n");
		return 1;
	} else {
		printf("%s\n", arg_msg);
		return -1;
	}
}

int main(int argc, char* argv[]) {
	// must be at least 3 chars in the alphabet
	//char alphabet[] = {' ', 'e', 't', 'a', 'o', 'n', 'h', 'i', 's', 'r', 'd', 'l', 'u', '\n', 'm', 'c', 'w', 'f', 'g', 'y', ',', 'p', 'b', '.', 'v', 'k', 'I', 'T', 'A', 'H', 'M', 'S', 'W', 'B', 'P', 'x', 'E', 'C', 'j', 'N', 'q', 'O', 'R', 'D', 'L', 'G', 'F', 'J', 'Y', 'z', 'V', 'K', 'U', 'X', 'Q', 'Z', '\3'};
	//int freq[] = {2658742, 1542772, 1091273, 982887, 941354, 852308, 791580, 791358, 764140, 707177, 549359, 491988, 346276, 324184, 297430, 286860, 281933, 261909, 249326, 233778, 222004, 195086, 173859, 157223, 115457, 99321, 64695, 40921, 28361, 27222, 24017, 20985, 18653, 17564, 17149, 16759, 14989, 14498, 13195, 12781, 11863, 11612, 10856, 10758, 10488, 10299, 9890, 7918, 7670, 7629, 4984, 3230, 2614, 1547, 858, 357, 0};
	
	int freq[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 324184, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2658742, 17559, 71754, 16, 35, 19, 39, 41906, 3649, 3660, 1763, 7, 222004, 54237, 157223, 477, 1246, 2740, 1024, 750, 598, 678, 502, 493, 1088, 512, 9386, 22636, 0, 11, 9, 16094, 33, 28361, 17564, 14498, 10758, 14989, 9890, 10299, 27222, 64695, 7918, 3230, 10488, 24017, 12781, 11612, 17149, 858, 10856, 20985, 40921, 2614, 4984, 18653, 1547, 7670, 357, 604, 0, 605, 0, 8753, 0, 982887, 173859, 286860, 549359, 1542772, 261909, 249326, 791580, 791358, 13195, 99321, 491988, 297430, 852308, 941354, 195086, 11863, 707177, 764140, 1091273, 346276, 115457, 281933, 16759, 233778, 7629, 13, 36, 13, 0, 0};
	
	char* inFile;
	char* outFile;
	int phase = handleArgs(argc, argv, &inFile, &outFile); // 0 == encode, 1 == decode
	Node** nodes = createArrayOfNodes(freq, NALPHABET);
	Node* root = createTree(nodes, NALPHABET);
	
	if (phase == -1) {
		return -1;
	} else if (phase == 0) {
		// encode
		HuffCode huffcodes[MAXASCII];
		getBitStrings(huffcodes, root, 0, 0);
		printHuffCodes(huffcodes, NALPHABET);
		FILE* f_out = fopen(outFile == NULL ? "output.bin" : outFile, "wb");
		FILE* f_in = fopen(inFile, "r");
		encode(f_out, f_in, huffcodes);
		fclose(f_out);
		fclose(f_in);
	} else {
		// decode
		FILE* f_out = fopen(outFile == NULL ? "output.txt" : outFile, "w");
		FILE* f_in = fopen(inFile, "rb");
		decode(f_out, f_in, root);
		fclose(f_out);
		fclose(f_in);
		return;
	}
	return 0;
}