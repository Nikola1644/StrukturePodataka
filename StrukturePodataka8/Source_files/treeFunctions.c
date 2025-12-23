#define _CRT_SECURE_NO_WARNINGS
#include "../Header_files/treeFunctions.h"
#include<stdio.h>
#include<stdlib.h>

Position treeInitialize(int value) {
	Position element = (Position)malloc(sizeof(SearchTree));
	if (!element)
		return NULL;
	element->value = value;
	element->parent = NULL;
	element->leftChild = NULL;
	element->rightChild = NULL;

	return element;
}

Position addElement(Position root, int value, Position parent) {
	if (root == NULL) {
		Position newElement = treeInitialize(value);
		newElement->parent = parent;
		return newElement;
	}

	if (value < root->value)
		root->leftChild = addElement(root->leftChild, value, root);
	else if (value > root->value)
		root->rightChild = addElement(root->rightChild, value, root);
	else
		printf("Element vec postoji u stablu!\n");
	
	return root;

}


int deleteElement(int value, Position root) {

	Position element = findElement(value, root);
	if (!element)
		return -1;

	if (element->leftChild && element->rightChild) {

		Position replacement = element->rightChild;
		while (replacement->leftChild != NULL)
			replacement = replacement->leftChild;

		element->value = replacement->value;
		return deleteElement(replacement->value, element->rightChild);
	}

	Position child = NULL;
	if (element->leftChild)
		child = element->leftChild;
	else
		child = element->rightChild;

	if (element->parent == NULL) {
		if (child)
			child->parent = NULL;
	}
	else {
		Position parent = element->parent;

		if (parent->leftChild == element)
			parent->leftChild = child;
		else
			parent->rightChild = child;

		if (child)
			child->parent = parent;
	}

	free(element);
	return 0;
}



Position findElement(int value, Position root) {
	if (root == NULL) {
		printf("Trazeni element nije pronaden!\n");
		return NULL;
	}
	if (value == root->value)
		return root;
	else if (value < root->value)
		return findElement(value, root->leftChild);
	else
		return findElement(value, root->rightChild);
}

int printPostorder(int depth, Position root) {
	if (!root)
		return 0;
	printPostorder(depth + 1, root->leftChild);
	printPostorder(depth + 1, root->rightChild);
	printf("%*s%d\n", depth * 2, "", root->value);
	return 0;
}
int printPreorder(int depth, Position root) {
	if (!root)
		return 0;
	printf("%*s%d\n", depth * 2, "", root->value);
	printPreorder(depth + 1, root->leftChild);
	printPreorder(depth + 1, root->rightChild);
	
	return 0;
}
int printInorder(int depth, Position root) {
	if (!root) return 0;

	printInorder(depth + 1, root->leftChild);
	printf("%*s%d\n", depth * 2, "", root->value);
	printInorder(depth + 1, root->rightChild);

	return 0;
}
int printLevel(Position root, int level) {
	if (!root) return;

	if (level == 1)	printf("%d ", root->value);
	else {
	
		printLevel(root->leftChild, level - 1);
		printLevel(root->rightChild, level - 1);
	}
	return 0;
}

int printLevelorder(Position root) {
	for (int i = 1; i <= treeHeight(root); i++) {
		printLevel(root, i);
		printf("\n");
	}
	return 0;
}
int treeHeight(Position root) {
	if (root == NULL)
		return 0;

	int leftHeight = treeHeight(root->leftChild);
	int rightHeight = treeHeight(root->rightChild);

	return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1; //Uzm
}

int freeTree(Position root) {
	if (root == NULL)
		return 0;

	freeTree(root->leftChild);
	freeTree(root->rightChild);
	free(root);

	return 0;
}
