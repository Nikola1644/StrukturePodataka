#define _CRT_SECURE_NO_WARNINGS

#include "../Header/receipts.h"
#include "../Header/items.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Kreira novi item i popunjava njegove podatke
itemPos createItem(char name[], int quantity, double price) {
	itemPos newElement = (itemPos)malloc(sizeof(Item)); // alokacija memorije za novi artikal
	if (!newElement) return NULL;

	strcpy(newElement->name, name);     // kopiranje imena artikla
	newElement->quantity = quantity;   // koli?ina artikla
	newElement->price = price;         // cijena artikla
	newElement->nextItem = NULL;       // sljede?i pokaziva? postavljen na NULL
	return newElement;
}

// Inicijalizira dummy head za listu artikala
itemPos itemInitialize() {
	itemPos P = (itemPos)malloc(sizeof(Item)); // alokacija dummy elementa
	if (!P) return NULL;

	strcpy(P->name, "");   // prazno ime
	P->quantity = 0;      // po?etna koli?ina 0
	P->price = 0.0;       // po?etna cijena 0
	P->nextItem = NULL;  // lista je zasad prazna

	return P;
}

// Dodaje artikal u sortiranu listu po imenu
int addItemSorted(receiptPos receipt, char name[], int quantity, double price) {
	itemPos element = createItem(name, quantity, price); // kreiranje novog artikla

	itemPos prev = receipt->Item;        // dummy head
	itemPos curr = prev->nextItem;       // prvi stvarni element

	// pronalazak mjesta za sortirani unos
	while (curr && strcmp(curr->name, name) < 0) {
		prev = curr;
		curr = curr->nextItem;
	}

	// umetanje novog elementa u listu
	element->nextItem = curr;
	prev->nextItem = element;

	return 0;
}

// Ra?una ukupnu koli?inu i cijenu odre?enog artikla u zadanom vremenskom rasponu
int itemPriceAndQuantity(receiptPos P, char name[], char from[], char to[])
{
	int totalQuantity = 0;  // ukupna koli?ina
	double totalPrice = 0; // ukupna cijena

	P = P->nextReceipt;  // preskakanje dummy head ra?una

	while (P != NULL) {

		// provjera je li datum u zadanom rasponu
		if (strcmp(P->date, from) >= 0 && strcmp(P->date, to) <= 0) {

			if (P->Item != NULL) {

				itemPos itemTemp = P->Item->nextItem; // preskakanje dummy head artikala

				while (itemTemp != NULL) {
					// ako se ime poklapa s traženim artiklom
					if (strcmp(itemTemp->name, name) == 0) {
						totalQuantity += itemTemp->quantity; // zbrajanje koli?ine
						totalPrice += itemTemp->quantity * itemTemp->price; // zbrajanje cijene
					}
					itemTemp = itemTemp->nextItem;
				}
			}
		}

		P = P->nextReceipt; // prelazak na sljede?i ra?un
	}

	// ispis rezultata
	printf("From %s to %s, a total of %d %s were purchased, it costed %.2f euros.\n",
		from, to, totalQuantity, name, totalPrice);

	return 0;
}

// Osloba?anje memorije svih artikala u listi
int freeItems(itemPos P) {
	itemPos temp;

	while (P) {
		temp = P;            // spremanje trenutnog elementa
		P = P->nextItem;    // prelazak na sljede?i
		free(temp);         // osloba?anje memorije
	}

	return 0;
}