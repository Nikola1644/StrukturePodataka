#define _CRT_SECURE_NO_WARNINGS

#include "../Header/receipts.h"
#include "../Header/items.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Inicijalizacija dummy head-a za listu ra?una
int createReceiptList(receiptPos P)
{
    if (!P) return -1;

    P->nextReceipt = NULL;  // lista je na po?etku prazna
    P->Item = NULL;         // još nema artikala

    strcpy(P->date, "0000-00-00"); // dummy datum

    return 0;
}

// Kreira novi ra?un s odre?enim datumom
receiptPos createReceipt(char date[]) {
    receiptPos newReceipt = (receiptPos)malloc(sizeof(Receipt));
    if (!newReceipt) return NULL;

    strcpy(newReceipt->date, date); // spremanje datuma
    newReceipt->nextReceipt = NULL;

    newReceipt->Item = itemInitialize(); // inicijalizacija dummy head-a za artikle

    return newReceipt;
}

// Broji koliko ima stvarnih ra?una u listi
int countReceipts(receiptPos P) {
    int count = 0;
    P = P->nextReceipt; // preskakanje dummy head

    while (P) {
        count++;
        P = P->nextReceipt;
    }

    return count;
}

// U?itava popis ra?una i njihove stavke iz datoteka
int createReceipts(receiptPos head)
{
    FILE* file = fopen("Racuni/racuni.txt", "r"); // otvaranje glavne datoteke s popisom ra?una

    if (file == NULL) {
        printf("Ne mogu otvoriti racuni.txt!\n"); // greška ako se ne može otvoriti
        return -1;
    }

    char buffer[256];

    // ?itanje imena pojedina?nih ra?una
    while (fgets(buffer, sizeof(buffer), file)) {

        buffer[strcspn(buffer, "\r\n")] = 0; // uklanjanje novog reda

        char fullPath[300];
        strcpy(fullPath, "Racuni/");  // putanja do direktorija s ra?unima
        strcat(fullPath, buffer);    // dodavanje imena datoteke

        FILE* item = fopen(fullPath, "r"); // otvaranje pojedina?nog ra?una

        if (item == NULL) {
            printf("Ne mogu otvoriti: %s\n", fullPath);
            continue;
        }

        char itemBuffer[256];
        fgets(itemBuffer, sizeof(itemBuffer), item); // ?itanje datuma
        itemBuffer[strcspn(itemBuffer, "\r\n")] = 0;

        receiptPos newReceipt = addReceiptSorted(head, itemBuffer); // dodavanje ra?una u sortiranu listu

        // ?itanje svih artikala iz ra?una
        while (fgets(itemBuffer, sizeof(itemBuffer), item)) {

            char* name = strtok(itemBuffer, ",");       // ime artikla
            char* quantity = strtok(NULL, ",");         // koli?ina
            char* price = strtok(NULL, ",");            // cijena

            name[strcspn(name, "\r\n")] = 0;
            quantity[strcspn(quantity, "\r\n")] = 0;
            price[strcspn(price, "\r\n")] = 0;

            // uklanjanje razmaka na po?etku
            while (*name == ' ') name++;
            while (*quantity == ' ') quantity++;
            while (*price == ' ') price++;

            // dodavanje artikla u sortiranu listu artikala
            addItemSorted(newReceipt, name, atoi(quantity), atof(price));
        }

        fclose(item); // zatvaranje datoteke pojedina?nog ra?una
    }

    fclose(file); // zatvaranje glavne datoteke racuni.txt
    return 0;
}

// Dodaje novi ra?un u sortiranu listu prema datumu
receiptPos addReceiptSorted(receiptPos P, char date[])
{
    receiptPos newReceipt = (receiptPos)malloc(sizeof(Receipt));
    if (!newReceipt)
        return NULL;

    strcpy(newReceipt->date, date); // spremanje datuma
    newReceipt->nextReceipt = NULL;
    newReceipt->Item = itemInitialize();   // dummy head za artikle

    receiptPos prev = P;
    receiptPos current = P->nextReceipt;

    // pronalazak mjesta za sortirani unos
    while (current != NULL && strcmp(current->date, date) < 0) {
        prev = current;
        current = current->nextReceipt;
    }

    newReceipt->nextReceipt = current; // umetanje u listu
    prev->nextReceipt = newReceipt;

    return newReceipt;
}

// Ispis svih ra?una i njihovih artikala
int printReceipts(receiptPos P)
{
    receiptPos curr = P->nextReceipt; // preskakanje dummy head

    while (curr != NULL) {
        printf("Date: %s\n", curr->date);

        itemPos item = curr->Item->nextItem; // preskakanje dummy head artikala
        while (item != NULL) {
            printf("  %s, %d, %.2lf\n",
                item->name,
                item->quantity,
                item->price);
            item = item->nextItem;
        }

        printf("\n");
        curr = curr->nextReceipt;
    }

    return 0;
}

// Osloba?anje memorije svih ra?una i njihovih artikala
int freeReceipts(receiptPos P)
{
    receiptPos temp;

    while (P != NULL) {

        freeItems(P->Item); // osloba?anje svih artikala u ra?unu

        temp = P;
        P = P->nextReceipt; // prelazak na sljede?i ra?un
        free(temp);         // osloba?anje memorije ra?una
    }

    return 0;
}