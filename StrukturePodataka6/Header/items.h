#ifndef ITEMS_H
#define ITEMS_H

typedef struct Receipt* receiptPos;
typedef struct Item* itemPos;

typedef struct Item{
	char name[50];
	int quantity;
	double price;

	itemPos nextItem;
}Item;
itemPos itemInitialize();
itemPos createItem(char name[], int quantity, double price);
int addItemSorted(receiptPos receipt, char name[], int quantity, double price);
int itemPriceAndQuantity(receiptPos P, char name[], char from[], char to[]);
int freeItems(itemPos P);

#endif