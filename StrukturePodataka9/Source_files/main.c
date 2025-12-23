#include "../Header_files/treeFunctions.h"   // funkcije i strukture za rad s binarnim stablom
#include "../Header_files/fileFunctions.h"   // funkcije za ispis stabla u datoteku
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand((unsigned)time(NULL));   // inicijalizacija generatora slucajnih brojeva

    int arr[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 }; // zadani niz brojeva
    int n = 10;                                  // broj elemenata u nizu

    Position root = NULL; // po etno prazno stablo

    // stvaranje binarnog stabla iz zadanog niza
    for (int i = 0; i < n; i++)
        root = insertInTree(root, arr[i]);

    printf("Preorder ispis: \n");
    printPreorder(root, 0); // preorder ispis stabla (radi provjere strukture)

    // otvaranje datoteke za upis inorder ispisa
    FILE* f = fopen("inorder.txt", "w");
    if (!f) {
        printf("Greska pri otvaranju datoteke\n");
        return 1;
    }

    // inorder ispis stabla prije replace funkcije
    fprintf(f, "Inorder prije replace:\n");
    inorderPrintToFile(root, f);
    fprintf(f, "\n");

    // zamjena vrijednosti svakog cvora sumom njegovih potomaka
    replaceTree(root);

    // inorder ispis stabla nakon replace funkcije
    fprintf(f, "Inorder nakon replace:\n");
    inorderPrintToFile(root, f);
    fprintf(f, "\n");

    fclose(f);      // zatvaranje datoteke
    freeTree(root); // oslobađanje memorije stabla

    return 0;
}