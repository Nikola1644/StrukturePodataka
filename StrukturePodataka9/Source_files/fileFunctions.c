#include "../Header_files/fileFunctions.h"

int inorderPrintToFile(Position root, FILE* file) {
	if (root == NULL)
		return;

	inorderPrintToFile(root->leftChild, file);
	fprintf(file, "%d ", root->value);
	inorderPrintToFile(root->rightChild, file);

	return 0;
}