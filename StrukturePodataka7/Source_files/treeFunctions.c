#define _CRT_SECURE_NO_WARNINGS
#include "../Header_files/treeFunctions.h"
#include "../Header_files/stackFunctions.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

Position directoryInitialize(char name[]) {
	Position newElement = (Position)malloc(sizeof(directory));
	if (!newElement)
		return NULL;
	strcpy(newElement->name, name);
	newElement->firstChild = NULL;
	newElement->nextChild = NULL;

	return newElement;
}

int makeDirectory(Stack StackP, char name[]) {
	if (StackP->next == NULL) {
		printf("Stog je prazan!\n");
		return -1;
	}

	Position curr = StackP->next->dir;
	addDirectorySorted(curr, name);

	return 0;
}

int addDirectorySorted(Position curr, char name[]) {

	Position check = curr->firstChild;
	while (check) {
		if (strcmp(check->name, name) == 0) {
			printf("Direktorij s imenom '%s' vec postoji!\n", name);
			return -1;
		}
		check = check->nextChild;
	}

	Position element = directoryInitialize(name);
	if (!element)
		return -1;

	if (!curr->firstChild || strcmp(curr->firstChild->name, name) > 0) {
		element->nextChild = curr->firstChild;
		curr->firstChild = element;
		return 0;
	}

	Position temp = curr->firstChild;
	while (temp->nextChild && strcmp(temp->nextChild->name, name) < 0) {
		temp = temp->nextChild;
	}

	element->nextChild = temp->nextChild;
	temp->nextChild = element;

	return 0;
}

int printChildDirectories(Stack StackP) {
	Position curr = StackP->next->dir;
	Position temp = curr->firstChild;

	if (!temp) {
		printf("Direktorij je prazan!");
		return -1;
	}
	while (temp) {
		printf("%s\n", temp->name);
		temp = temp->nextChild;
	}
	return 0;
}

int cdDirectory(Stack StackP, char name[]) {
	Position curr = StackP->next->dir;
	Position temp = curr->firstChild;

	while (temp && strcmp(temp->name, name) != 0) {
		temp = temp->nextChild;
	}

	if (!temp) {
		printf("Direktorij nije pronaden!\n");
		return 0;
	}
	push(StackP, temp);
	return 0;
}

int renameDirectory(Position curr, char oldName[], char newName[]) {
	Position temp = curr->firstChild;

	while (temp && strcmp(temp->name, oldName) != 0) {
		temp = temp->nextChild;
	}
	if (!temp) {
		printf("Direktorij nije pronaden!\n");
		return 0;
	}

	strcpy(temp->name, newName);
	return 0;
}

int deleteDirectory(Position curr, char name[]) {
	Position temp = curr->firstChild;
	Position prev = NULL;

	while (temp && strcmp(temp->name, name) != 0) {
		prev = temp;
		temp = temp->nextChild;
	}
	if (!temp) {
		printf("Direktorij nije pronaden!\n");
		return 0;
	}
	if (!prev) {
		curr->firstChild = temp->nextChild;
	}
	else
		prev->nextChild = temp->nextChild;
	freeTree(temp);

	return 0;
}
int freeTree(Position dirP) {
	if (!dirP)
		return 0;
	freeTree(dirP->firstChild);
	freeTree(dirP->nextChild);
	free(dirP);

	return 0;
}