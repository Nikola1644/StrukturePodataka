#define _CRT_SECURE_NO_WARNINGS
#include "../Header_files/stackFunctions.h"
#include<stdio.h>
#include<stdlib.h>

Stack stackInitialize(Position dir) {
	Stack newElement = (Stack)malloc(sizeof(dirPosition));
	if (!newElement)
		return NULL;
	newElement->dir = dir;
	newElement->next = NULL;

	return newElement;
}

int push(Stack StackP, Position dir) {
	Stack element = stackInitialize(dir);
	element->next = StackP->next;
	StackP->next = element;

	return 0;
}

int pop(Stack StackP) {
	if (StackP->next->next == NULL) {
		printf("Nemoguce izaci iz C: direktorija!");
		return 0;
	}
	
	Stack temp = StackP->next;
	StackP->next = temp->next;
	free(temp);
	return 0;
}

int freeStack(Stack StackP) {
	while (StackP != NULL) {
		Stack temp = StackP;
		StackP = StackP->next;
		free(temp);
	}
	return 0;
}