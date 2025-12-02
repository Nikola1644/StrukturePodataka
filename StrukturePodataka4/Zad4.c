#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


typedef struct Element* Position;

// Struktura jednog člana polinoma
typedef struct Element {
    int coef;      // koeficijent
    int pow;       // eksponent
    Position next; // pokazivač na sljedeći element
} Element;


Position initialize();
int countRows();
bool checkIsNumber(char buffer[50]);
int readFromFile(int numberOfRows, Position P[]);
int sortInsert(Position head, Position novi);
int chooseOperation(Position P[], int numberOfRows);
int add(Position P[], int numberOfRows);
int multiply(Position P[], int numberOfRows);
int printList(Position head);
Position checkExp(Position head, int pow);
int freeList(Position head);


int main() {

    int numberOfRows = countRows();   // broj redaka (polinoma) u datoteci

    // Alokacija polja pokazivača na liste polinoma
    Position* P = malloc(numberOfRows * sizeof(Position));
    if (!P) {
        printf("Greska pri alokaciji memorije!\n");
        return -1;
    }

    readFromFile(numberOfRows, P);    // učitaj polinome iz datoteke

    chooseOperation(P, numberOfRows); // korisnik bira zbrajanje ili množenje

    printf("\nRezultat operacije je:\n");
    printList(P[0]);                  // ispis konačnog polinoma
    printf("\n");

    freeList(P[0]);                   // oslobađanje memorije
    return 0;
}



// Stvara novi čvor 
Position initialize() {
    Position new = (Position)malloc(sizeof(Element));
    if (!new) {
        printf("Nema dovoljno memorije!\n");
        return NULL;
    }

    new->coef = 0;
    new->pow = 0;
    new->next = NULL;
    return new;
}



// Provjerava je li pročitani token zapravo broj
bool checkIsNumber(char buffer[50]) {

    if ((buffer[0] == '-' && isdigit(buffer[1])) || isdigit(buffer[0]))
        return true;

    return false;
}


// Umeće element u sortiranu listu prema eksponentu 
int sortInsert(Position head, Position new) {

    // Ako lista ima samo head
    if (head->next == NULL) {
        head->next = new;
        return 0;
    }

    Position temp = head;

    // Traži se mjesto gdje eksponent treba biti umetnut
    while (temp->next != NULL && new->pow < temp->next->pow)
        temp = temp->next;

    new->next = temp->next;
    temp->next = new;

    return 0;
}



// Ispis polinoma u standardnom obliku
int printList(Position head) {

    Position temp = head->next;
    int first = 0;

    while (temp != NULL) {

        // Stavljanje plusa između pozitivnih članova
        if (first && temp->coef > 0)
            printf(" + ");

        printf("%d", temp->coef);

        // pravilni ispis x-a i eksponenta
        if (temp->pow == 0)
            ;
        else if (temp->pow == 1)
            printf("x");
        else
            printf("x^%d", temp->pow);

        first = 1;
        temp = temp->next;
    }

    return 0;
}



// Briše cijelu listu iz memorije
int freeList(Position head) {

    Position temp = head;

    while (temp != NULL) {
        Position next = temp->next;
        free(temp);
        temp = next;
    }

    return 0;
}



// Broji koliko redaka (polinoma) se nalazi u datoteci
int countRows() {

    FILE* file = fopen("Polinomi.txt", "r");
    if (!file) {
        printf("Ne mogu otvoriti datoteku!\n");
        return 0;
    }

    if (fgetc(file) == EOF) {  // provjera je li prazna
        printf("Datoteka je prazna!\n");
        return 0;
    }

    rewind(file);

    int count = 0;
    int ch;

    // Brojenje znakova novog reda
    while ((ch = fgetc(file)) != EOF)
        if (ch == '\n')
            count++;

    fclose(file);
    return count;
}



// Učitava sve polinome iz datoteke
int readFromFile(int numberOfRows, Position P[]) {

    FILE* file = fopen("Polinomi.txt", "r");
    if (!file) {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    char buffer[256];

    for (int i = 0; i < numberOfRows; i++) {

        P[i] = initialize();  // stvori head element liste

        // učitavanje jednog retka
        if (!fgets(buffer, sizeof(buffer), file)) {
            printf("Nedovoljno redaka u datoteci!\n");
            break;
        }

        char* token = strtok(buffer, " \t\r\n");  // prvi token

        while (token != NULL) {

            if (!checkIsNumber(token)) {
                printf("Koeficijent nije broj!\n");
                fclose(file);
                return -1;
            }

            Position new = initialize();
            new->coef = atoi(token);  // koeficijent

            token = strtok(NULL, " \t\r\n");

            if (token == NULL || !checkIsNumber(token)) {
                printf("Eksponent nedostaje!\n");
                fclose(file);
                return -1;
            }

            new->pow = atoi(token);  // eksponent

            sortInsert(P[i], new);   // ubaci u sortirani polinom

            token = strtok(NULL, " \t\r\n");
        }
    }

    fclose(file);
    return 0;
}



// Korisnik bira operaciju: zbrajanje ili množenje
int chooseOperation(Position P[], int numberOfRows) {

    int n;

    printf("Zelite li zbrojiti (0) ili pomnoziti (1) polinome?\n");
    scanf("%d", &n);

    while (n != 0 && n != 1) {
        printf("Pogresan unos, pokusajte ponovno:\n");
        scanf("%d", &n);
    }

    if (n == 0)
        add(P, numberOfRows);
    else
        multiply(P, numberOfRows);

    return 0;
}



// Traži postoji li element s istim eksponentom u listi
Position checkExp(Position head, int pow) {

    Position temp = head->next;

    while (temp != NULL && temp->pow != pow)
        temp = temp->next;

    return temp;
}



// Zbrajanje svih polinoma u P[] rezultat ide u P[0]
int add(Position P[], int numberOfRows) {

    for (int i = numberOfRows - 1; i > 0; i--) {

        Position poly1 = P[i]->next;  // polinom koji dodajemo

        while (poly1 != NULL) {

            Position poly2 = P[i - 1]->next; // polinom u koji dodajemo
            Position nextPoly1 = poly1->next; // čuvamo sljedeći čvor

            // pronalazak točnog mjesta u poly2
            while (poly2->next != NULL && poly2->next->pow > poly1->pow)
                poly2 = poly2->next;

            // ako postoji isti eksponent samo zbroji koeficijente
            if (poly2->next != NULL && poly2->next->pow == poly1->pow) {
                poly2->next->coef += poly1->coef;
            }
            else {
                // inače napravi novi čvor i ubaci sortirano
                Position new = initialize();
                new->coef = poly1->coef;
                new->pow = poly1->pow;
                sortInsert(P[i - 1], new);
            }

            poly1 = nextPoly1;
        }

        freeList(P[i]); // polinom je sada prebačen
    }

    return 0;
}



// Množenje polinoma rezultat ide u P[0]
int multiply(Position P[], int numberOfRows) {

    for (int i = numberOfRows - 1; i > 0; i--) {

        Position result = initialize();  // novi rezultat
        Position poly1 = P[i]->next;

        while (poly1 != NULL) {

            Position poly2 = P[i - 1]->next;

            while (poly2 != NULL) {

                // stvori novi član 
                Position new = initialize();
                new->coef = poly1->coef * poly2->coef;
                new->pow = poly1->pow + poly2->pow;

                // ako eksponent već postoji zbroji koeficijente
                Position check = checkExp(result, new->pow);

                if (check)
                    check->coef += new->coef;
                else
                    sortInsert(result, new);

                poly2 = poly2->next;
            }

            poly1 = poly1->next;
        }

        freeList(P[i - 1]);    // briši stari polinom
        P[i - 1] = result;     // zamijeni ga novim
        freeList(P[i]);      // briši izvorni faktor
    }

    return 0;
}