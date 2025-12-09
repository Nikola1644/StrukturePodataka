#ifndef RECEIPTS_H
#define RECEIPTS_H

typedef struct Item* itemPos;
typedef struct Receipt* receiptPos;
typedef struct Receipt {
	char date[11];
	receiptPos nextReceipt;
	itemPos Item;

}Receipt;

int createReceiptList(receiptPos P);
receiptPos createReceipt(char date[]);
int countReceipts(receiptPos P);
int createReceipts(receiptPos P);
receiptPos addReceiptSorted(receiptPos P, char date[]);
int printReceipts(receiptPos P);
int freeReceipts(receiptPos P);


#endif