#define _CRT_SECURE_NO_WARNINGS   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Header_files/io.h"
#include "../Header_files/country.h"
#include "../Header_files/city.h"
#include "../Header_files/country_hash.h"

/* Cisti ulazni buffer nakon scanf poziva */
static void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void)
{
    int n = 0;

    /* Odabir nacina formiranja struktura */
    printf("Odaberi nacin formiranja struktura:\n");
    printf("1) Lista drzava (sort po nazivu i stablo gradova\n");
    printf("2) Stablo drzava (sort po nazivu i lista gradova\n");
    printf("3) HASH tablica drzava (11 mjesta) i stablo gradova\n"); //dodatak za 11 zad.
    printf("Unos: ");

    /* Ucitavanje izbora */
    if (scanf("%d", &n) != 1) {
        printf("Neispravan unos.\n");
        return 1;
    }
    clearInputBuffer();

    /* Opcija a: lista drzava + stablo gradova */
    if (n == 1) {

        /* Ucitavanje drzava i njihovih gradova */
        countryPosition head = createCountryListCityTree("drzave.txt");
        if (!head) {
            printf("Ne mogu ucitati drzave.txt ili podatke.\n");
            return 1;
        }

        /* Ispis svih drzava i gradova */
        printf("\n=== ISPIS (a) ===\n");
        countryListPrint(head);

        /* Pretraga */
        while (1) {
            char countryName[50];
            int minPop = 0;
            countryPosition found = NULL;

            /* Unos imena drzave */
            printf("\nUnesi ime drzave (ili 'exit' za kraj): ");
            if (scanf("%49s", countryName) != 1) break;

            if (strcmp(countryName, "exit") == 0) break;

            /* Unos minimalnog broja stanovnika */
            printf("Unesi minimalan broj stanovnika: ");
            if (scanf("%d", &minPop) != 1) {
                printf("Neispravan broj.\n");
                clearInputBuffer();
                continue;
            }

            /* Pretraga drzave u listi */
            found = countryListFind(head, countryName);
            if (!found) {
                printf("Drzava '%s' nije pronadena.\n", countryName);
                continue;
            }

            /* Ispis gradova s vise stanovnika od zadanog praga */
            printf("Gradovi u drzavi %s s vise od %d stanovnika:\n", found->name, minPop);
            cityTreePrintHigher(found->cityRoot, minPop);
        }

        /* Oslobadanje memorije */
        freeCountryList(head);
    }
    /* Opcija b: stablo drzava + lista gradova */
    else if (n == 2) {

        /* Ucitavanje drzava i njihovih gradova */
        countryPosition root = createCountryTreeCityList("drzave.txt");
        if (!root) {
            printf("Ne mogu ucitati drzave.txt ili podatke.\n");
            return 1;
        }

        /* Ispis svih drzava i gradova */
        printf("\n=== ISPIS (b) ===\n");
        countryTreePrintInOrder(root);

        /* Pretraga */
        while (1) {
            char countryName[50];
            int minPop = 0;
            countryPosition found = NULL;

            /* Unos imena drzave */
            printf("\nUnesi ime drzave (ili 'exit' za kraj): ");
            if (scanf("%49s", countryName) != 1) break;

            if (strcmp(countryName, "exit") == 0) break;

            /* Unos minimalnog broja stanovnika */
            printf("Unesi minimalan broj stanovnika: ");
            if (scanf("%d", &minPop) != 1) {
                printf("Neispravan broj.\n");
                clearInputBuffer();
                continue;
            }

            /* Pretraga drzave u stablu */
            found = countryTreeFind(root, countryName);
            if (!found) {
                printf("Drzava '%s' nije pronadena.\n", countryName);
                continue;
            }

            /* Ispis gradova s vise stanovnika od zadanog praga */
            printf("Gradovi u drzavi %s s vise od %d stanovnika:\n", found->name, minPop);
            cityListPrintHigher(found->cityP, minPop);
        }

        /* Oslobadanje memorije */
        freeCountryTree(root);
    }

    else if (n == 3) {

        /* Hash tablica od 11 bucket-a */
        countryPosition hashTable[SIZE] = { NULL };

        /* Ucitavanje drzava i njihovih gradova u hash tablicu */
        if (createCountryHashCityTree(hashTable, "drzave.txt") != 0) {
            printf("Ne mogu ucitati drzave.txt ili podatke!\n");
            return 1;
        }

        /* Ispis cijele hash tablice */
        printf("\n=== ISPIS (HASH) ===\n");
        countryHashPrint(hashTable);

        /* Pretraga */
        while (1) {
            char countryName[50];
            int minPop = 0;
            countryPosition found = NULL;

            /* Unos imena drzave */
            printf("\nUnesi ime drzave (ili 'exit' za kraj): ");
            if (scanf("%49s", countryName) != 1)
                break;

            /* Izlaz iz petlje */
            if (strcmp(countryName, "exit") == 0)
                break;

            /* Unos minimalnog broja stanovnika */
            printf("Unesi minimalan broj stanovnika: ");
            if (scanf("%d", &minPop) != 1) {
                printf("Neispravan broj unesen!\n");
                clearInputBuffer();
                continue;
            }

            /* Pretraga drzave u hash tablici */
            found = countryHashFind(hashTable, countryName);
            if (!found) {
                printf("Drzava '%s' nije pronadena.\n", countryName);
                continue;
            }

            /* Ispis gradova s vise stanovnika od zadanog praga */
            printf("Gradovi u drzavi %s s vise od %d stanovnika:\n",
                found->name, minPop);
            cityTreePrintHigher(found->cityRoot, minPop);
        }

        /* Oslobadanje memorije */
        freeCountryHash(hashTable);
    }

    /* Pogresan odabir */
    else {
        printf("Nepostojeca opcija.\n");
        return 1;
    }

    printf("\nKraj programa.\n");
    return 0;
}