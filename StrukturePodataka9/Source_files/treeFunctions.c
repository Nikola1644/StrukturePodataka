#include "../Header_files/treeFunctions.h"
#include<stdio.h>
#include<stdlib.h>

Position treeInitialize(int value) {
	Position newElement = (Position)malloc(sizeof(Tree));
	if (!newElement) {
		printf("Allocation error!\n");
		return NULL;
	}

	newElement->value = value;
	newElement->leftChild = NULL;
	newElement->rightChild = NULL;

	return newElement;
}

Position insertInTree(Position root, int value) {
	if (!root)
		return treeInitialize(value);
	if (value >= root->value)
		root->leftChild = insertInTree(root->leftChild, value);
	else
		root->rightChild = insertInTree(root->rightChild, value);

	return root;
}

int replaceTree(Position root) {
	if (root == NULL)
		return 0;

	int sumLeft = replaceTree(root->leftChild);
	int sumRight = replaceTree(root->rightChild);
	int  oldValue = root->value;
	root->value = sumLeft + sumRight;

	return oldValue + sumLeft + sumRight;

}

int printPreorder(Position root, int depth) {
	if (root == NULL)
		return;
	for (int i = 0; i < depth; i++) {
		printf("- ");
	}
	printf("%d\n", root->value);

	printPreorder(root->leftChild, depth + 1);
	printPreorder(root->rightChild, depth + 1);
	return 0;
}

int freeTree(Position root) {
	if (root == NULL)
		return;
	freeTree(root->leftChild);
	freeTree(root->rightChild);
	free(root);

	return 0;
}