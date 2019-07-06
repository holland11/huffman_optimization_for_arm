#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman_coding.h"
#include "huffman_debug.h"
#include "huffman_tree.h"
#include "huffman_utils.h"

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
	build();
	// DICT is an array mapping ASCII codes to huffman codes 
	// (ex. DICT[32] == HuffCode{.code=6, .len=3} which means char(32) (" ") is 110)
	// TREE is an array representation of the huffman tree. 
	// you can use a code's first 3 bits to index into the correct subtree of the array
	// (ex. you see code 011 which is equal to 4 so you can jump right to TREE[4] and continue traversing the tree)
	// (ex. TREE[1] = HuffNode{.letter=128, .left=7, .right=8}
	// letter=128 means it's an internal node
	// left=7 means to get to the left child, add 7 to the pointer (or move 7 indeces forward in the array)

	char* inFile;
	char* outFile;
	int phase = handleArgs(argc, argv, &inFile, &outFile); // 0 == encode, 1 == decode
	
	if (phase == -1) {
		return -1;
	} else if (phase == 0) {
		// encode
		FILE* f_out = fopen(outFile == NULL ? "output.bin" : outFile, "wb");
		FILE* f_in = fopen(inFile, "r");
		encode(f_out, f_in, DICT);
		fclose(f_out);
		fclose(f_in);
	} else {
		// decode
		FILE* f_out = fopen(outFile == NULL ? "output.txt" : outFile, "w");
		FILE* f_in = fopen(inFile, "rb");
		decode(f_out, f_in, TREE);
		fclose(f_out);
		fclose(f_in);
	}
	return 0;
}