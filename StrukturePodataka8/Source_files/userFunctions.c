#define _CRT_SECURE_NO_WARNINGS
#include "../Header_files/treeFunctions.h"
#include "../Header_files/userFunctions.h"
#include<stdio.h>
#include<stdlib.h>

int chooseFunction() {
	Position root = NULL;
	int value, n;
	printf("Unesite vrijednost root elementa: \n");
	scanf("%d", &value);
	root = treeInitialize(value);

	while (1) {
		printf("\n --IZBORNIK-- \n");
		printf("1 -> Dodaj novi element\n");
		printf("2 -> Inorder ispis\n");
		printf("3 -> Preorder ispis\n");
		printf("4 -> Postorder ispis\n");
		printf("5 -> Level-order ispis\n");
		printf("6 -> Obrisi element\n");
		printf("7 -> Pronadi element\n");
		printf("8 -> Izlaz iz programa\n\n");
		printf("Odabir: ");
		scanf("%d", &n);

		switch (n) {
        case 1:
            printf("Unesi vrijednost: ");
            scanf("%d", &value);
            root = addElement(root, value, NULL);
            break;

        case 2:
            printf("\nInorder ispis:\n");
            printInorder(0, root);
            break;

        case 3:
            printf("\nPreorder ispis:\n");
            printPreorder(0, root);
            break;

        case 4:
            printf("\nPostorder ispis:\n");
            printPostorder(0, root);
            break;

        case 5:
            printf("\nLevel-order ispis:\n");
            printLevelorder(root);
            break;

        case 6:
            printf("Unesi vrijednost za brisanje: ");
            scanf("%d", &value);
            if (deleteElement(value, root) == EXIT_FAILURE)
                printf("Element ne postoji u stablu!\n");
            break;

        case 7:
            printf("Unesi vrijednost za trazenje: ");
            scanf("%d", &value);
            if (findElement(value, root))
                printf("Element je pronadjen!\n");
            else
                printf("Element nije pronadjen!\n");
            break;

        case 8:
            freeTree(root);
            printf("Izlaz iz programa.\n");
            return 0;

        default:
            printf("Pogresan odabir!\n");
        }
	}

	return 0;
}