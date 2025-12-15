#ifndef STACK_FUNCTIONS_H
#define STACK_FUNCTIONS_H

typedef struct directory* Position;
typedef struct dirPosition* Stack;

typedef struct dirPosition {
	Stack next;
	Position dir;
}dirPosition;

Stack stackInitialize(Position dir);
int push(Stack StackP, Position dir);
int pop(Stack StackP);
int freeStack(Stack StackP);

#endif

