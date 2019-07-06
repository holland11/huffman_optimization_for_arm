#include "huffman_debug.h"

void buildStaticArrays() {
	int freq[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 324184, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2658742, 17559, 71754, 16, 35, 19, 39, 41906, 3649, 3660, 1763, 7, 222004, 54237, 157223, 477, 1246, 2740, 1024, 750, 598, 678, 502, 493, 1088, 512, 9386, 22636, 0, 11, 9, 16094, 33, 28361, 17564, 14498, 10758, 14989, 9890, 10299, 27222, 64695, 7918, 3230, 10488, 24017, 12781, 11612, 17149, 858, 10856, 20985, 40921, 2614, 4984, 18653, 1547, 7670, 357, 604, 0, 605, 0, 8753, 0, 982887, 173859, 286860, 549359, 1542772, 261909, 249326, 791580, 791358, 13195, 99321, 491988, 297430, 852308, 941354, 195086, 11863, 707177, 764140, 1091273, 346276, 115457, 281933, 16759, 233778, 7629, 13, 36, 13, 0, 0};
	
	Node** nodes = createArrayOfNodes(freq, NALPHABET);
	Node* root = createTree(nodes, NALPHABET);
	
	HuffCode huffcodes[NALPHABET];
	getBitStrings(huffcodes, root, 0, 0);
	//printHuffCodes(huffcodes, NALPHABET);
	//printDictionary(huffcodes, NALPHABET);
	Node* tree_nodes[248]; // 255 nodes -7 bcz we trim the first 2 levels
	int index = 0;
	findThirdLevelNodes(root, tree_nodes, 0, &index);
	index = 8;
	traverseSubTrees(tree_nodes, &index);
}

void printDictionary(HuffCode huffcodes[], int length) {
	int i;
	for (i=0; i<length; i++) {
		printf("#define C%d { .code=%u, .len=%u }\n", i, huffcodes[i].code, huffcodes[i].len);
	}
}

void findThirdLevelNodes(Node* node, Node** subtrees, int depth, int* index) {
	if (depth == 3) {
		subtrees[*index] = node;
		(*index)++;
	} else {
		depth++;
		if (node->left != NULL) {
			findThirdLevelNodes(node->left, subtrees, depth, index);
		}
		if (node->right != NULL) {
			findThirdLevelNodes(node->right, subtrees, depth, index);
		}
	}
}

int analyzeTree(Node* node, int depth, int* count) {
	(*count)++;
	if (node->left == NULL && node->right == NULL) {
		return depth;
	} else {
		depth++;
		int temp1 = 0;
		int temp2 = 0;
		if (node->left != NULL) {
			temp1 = analyzeTree(node->left, depth, count);
		}
		if (node->right != NULL) {
			temp2 = analyzeTree(node->right, depth, count);
		}
		if (temp1 > temp2) return temp1;
		else return temp2;
	}
}

/*int fillTreeNodeArray(Node* node, Node** tree_nodes, int* index, int current) {
	int tempL;
	int tempR;
	if (node->left == NULL && node->right == NULL) {
		// leaf node
	} else {
		// internal node
		if (node->left != NULL) {
			tree_nodes[*index] = node->left;
			tempL = *index;
			(*index)++;
		}
		if (node->right != NULL) {
			tree_nodes[*index] = node->right;
			tempR = *index;
			(*index)++;
		}
	}
	printf("#define N%d { .letter=%d, .left=%d, .right=%d }\n", 
			current, node->letter, 
			(node->left != NULL) ? tempL : 0,
			(node->right != NULL) ? tempR : 0);
	if (node->left != NULL) {
		fillTreeNodeArray(node->left, tree_nodes, index, tempL);
	}
	if (node->right != NULL) {
		fillTreeNodeArray(node->right, tree_nodes, index, tempR);
	}
}*/

int fillTreeNodeArray(Node* node, ArrayNode arr[], int* index, int current) {
	int result = current-1;
	int tempL = 0, tempR = 0;
	if (!current) {
		result = *index;
		(*index)++;
	}
	if (node->left != NULL) {
		tempL = fillTreeNodeArray(node->left, arr, index, 0) - result;
	}
	if (node->right != NULL) {
		tempR = fillTreeNodeArray(node->right, arr, index, 0) - result;
	}
	
	arr[result].letter = node->letter;
	arr[result].left = tempL;
	arr[result].right = tempR;
	
	return result;
}

void traverseSubTrees(Node** tree_nodes, int* index) {
	/*
	tree 0 has height 0 and 1 nodes
	tree 1 has height 1 and 3 nodes
	tree 2 has height 1 and 3 nodes
	tree 3 has height 12 and 39 nodes
	tree 4 has height 3 and 7 nodes
	tree 5 has height 3 and 7 nodes
	tree 6 has height 0 and 1 nodes
	tree 7 has height 25 and 187 nodes
	*/
	int i;
	int order[] = {0,6,1,2,4,5,3,7};
	ArrayNode arr[248];
	for (i=0; i<8; i++) {
		int root = order[i];
		int temp = fillTreeNodeArray(tree_nodes[root], arr, index, root+1);
	}
	for (i=0; i<248; i++) {
		ArrayNode n = arr[i];
		printf("#define N%d { .letter=%u, .left=%d, .right=%d }\n",
			i, n.letter, n.left, n.right);
	}
}
  
void printNodes(Node** nodes, int length, int skip) {
	int i;
	printf("[\n");
	for (i=skip; i<length; i++) {
		printf("%c: %d\n", nodes[i]->letter, nodes[i]->freq_sum);
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
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->freq_sum); 
  
    // Process left child 
    print2DUtil(root->left, space); 
} 
  
// Wrapper over print2DUtil() 
void print2D(Node *root) 
{ 
   // Pass initial space count as 0 
   print2DUtil(root, 0); 
} 

void printHuffCodes(HuffCode huffcodes[], int length) {
	int i,j;
	for (i=0; i<length; i++) {
		HuffCode huffcode = huffcodes[i];
		printf("%d %d %d ", i, huffcode.len, huffcode.code);
		// len = 5, code = 5 (00000101) -> 00101
		for (j=huffcode.len-1; j>=0; j--) {
			int temp = (huffcode.code >> j) & 1;
			printf("%d",temp);
		}
		printf("\n");
	}
}