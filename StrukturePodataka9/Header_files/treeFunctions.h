#ifndef TREE_FUNCTIONS_H
#define TREE_FUNCTIONS_H

#include <stdio.h>   // potreban za printf u ispisnim funkcijama

typedef struct Tree* Position; // pokazivac na cvor binarnog stabla

// struktura cvora binarnog stabla
typedef struct Tree {
    int value;              // vrijednost cvora
    Position leftChild;     // pokazivač na lijevo podstablo
    Position rightChild;    // pokazivač na desno podstablo
} Tree;

// inicijalizacija novog cvora stabla
Position treeInitialize(int value);

// umetanje novog elementa u binarno stablo
Position insertInTree(Position root, int value);

// zamjena vrijednosti cvora sumom elemenata njegovih potomaka
int replaceTree(Position root);

// preorder ispis stabla (pomocna funkcija za provjeru)
int printPreorder(Position root, int depth);

// oslobadjanje memorije cijelog stabla
int freeTree(Position root);

#endif