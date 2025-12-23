#ifndef TREE_FUNCTIONS_H
#define TREE_FUNCTIONS_H

typedef struct SearchTree* Position;

typedef struct SearchTree {
	int value;
	Position parent;
	Position rightChild;
	Position leftChild;
}SearchTree;

Position treeInitialize(int value);
Position addElement(Position root, int value, Position parent);
int deleteElement(int value, Position root);
Position findElement(int value, Position root);
int printInorder(int depth, Position root);
int printPreorder(int depth, Position root);
int printPostorder(int depth, Position root);
int printLevelorder(Position root);
int treeHeight(Position root);
int freeTree(Position root);

#endif