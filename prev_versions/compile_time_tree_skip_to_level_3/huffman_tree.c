#include "huffman_tree.h"

int cmp_nodes(const void* a, const void* b) {
	Node* node_a = *(Node**)a;
	Node* node_b = *(Node**)b;
	return node_a->freq_sum - node_b->freq_sum;
}

Node** createArrayOfNodes(int* freq, int length) {
	int i;
	Node** nodes = (Node**)malloc(sizeof(Node*)*length);
	for (i=0; i<length; i++) {
		Node* node = (Node*)malloc(sizeof(Node));
		node->letter = i;
		node->freq_sum = freq[i];
		node->left = NULL;
		node->right = NULL;
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
		new_node->letter = length;
		new_node->freq_sum = node_a->freq_sum + node_b->freq_sum;
		new_node->left = node_a;
		new_node->right = node_b;
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