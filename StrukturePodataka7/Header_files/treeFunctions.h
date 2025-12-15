#ifndef TREE_FUNCTIONS_H
#define TREE_FUNCTIONS_H

typedef struct directory* Position;
typedef struct dirPosition* Stack;

typedef struct directory {
	char name[40];
	Position firstChild;
	Position nextChild;
}directory;

Position directoryInitialize(char name[]); //alokacija i postavljanje imena
int addDirectorySorted(Position curr, char name[]); // dodaje poddirektori abecedno
int makeDirectory(Stack StackP, char name[]); // kreira direktori u trenutnom direktoriju
int printChildDirectories(Stack StackP); // ispisuje sadrzaj direktorija 
int cdDirectory(Stack StackP, char name[]); // otvara direktorij koji je poddirektori trenutnI
int deleteDirectory(Position curr, char name[]);
int freeTree(Position dirP);

#endif