#define _CRT_SECURE_NO_WARNINGS

#include "../Header/receipts.h"
#include "../Header/items.h"

#include <stdio.h>
#include <stdlib.h>


int main() {
    Receipt P;                 // dummy head za račune
    createReceiptList(&P);     // inicijalizacija liste

    // učitavanje računa iz racuni.txt i pojedinačnih datoteka
    createReceipts(&P);

    // ispis svih računa i artikala
    printReceipts(&P);

    // upit po artiklu i vremenskom razdoblju
    itemPriceAndQuantity(&P, "Kruh", "2021-01-01", "2021-12-31");

    // oslobađanje memorije
    freeReceipts(P.nextReceipt);

    return 0;
}