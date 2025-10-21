#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 40
#define INITIALIZATION_ERROR -1

// Definicija strukture i pokazivaca na strukturu
typedef struct person* position;
typedef struct person {
    char firstName[MAX];
    char lastName[MAX];
    int birthYear;

    position next;

} person;

// Deklaracije funkcija
int insertStartPerson(position P, char firstName[MAX], char lastName[MAX], int birthYear);
int insertEndPerson(position P, char firstName[MAX], char lastName[MAX], int birthYear);
int deleteByLastName(position P, char lastName[MAX]);
position searchByLastName(position P, char lastName[MAX]);
int printList(position P);
int insertData(position newPerson, char firstName[MAX], char lastName[MAX], int birthYear);
int freeList(position P);

int main() {
    // Kreiramo prazan cvor koji sluzi kao glava liste (ne sadrzi stvarne podatke)
    struct person head = { .firstName = "", .lastName = "", .birthYear = 0, .next = NULL };
    position P = &head;

    // Dodaj osobu na pocetak liste
    insertStartPerson(P, "Nikola", "Nikolic", 2002);
    // Dodaj osobu na kraj liste
    insertEndPerson(P, "Petar", "Peric", 2000);
    //Ispis liste nakon dodavanja
    printf("Lista nakon dodavanja: \n");
    printList(P);
    // Obrisi osobu po prezimenu
    deleteByLastName(P, "Nikolic");
    //Ispis liste nakon brisanja
    printf("Lista nakon brisanja: \n");
    printList(P);
    // Oslobodi memoriju na kraju
    freeList(P);
}

int insertStartPerson(position P, char firstName[MAX], char lastName[MAX], int birthYear) {
    // Alociraj novi element u memoriji
    position newPerson = (position)malloc(sizeof(person));
    if (newPerson == NULL) {
        printf("Allocation error!\n");
        return -1;
    }

    // Postavi podatke u novi element
    insertData(newPerson, firstName, lastName, birthYear);

    // Uvezi novi element na pocetak liste
    newPerson->next = P->next;
    P->next = newPerson;

    return 0;
}

int printList(position P) {
    // Kreni od prvog stvarnog elementa (preskace head cvor)
    position q = P->next;
    while (q != NULL) {
        printf("%s %s %d \n", q->firstName, q->lastName, q->birthYear);
        q = q->next;
    }

    return 0;
}

int insertEndPerson(position P, char firstName[MAX], char lastName[MAX], int birthYear) {
    // Alociraj memoriju za novi element
    position newPerson = (position)malloc(sizeof(person));
    if (newPerson == NULL) {
        printf("Allocation error!\n");
        return -1;
    }

    // Pronadi zadnji element u listi
    position q = P;
    while (q->next != NULL)
        q = q->next;

    // Postavi podatke u novi element
    insertData(newPerson, firstName, lastName, birthYear);

    // Novi element postaje zadnji (next = NULL)
    q->next = newPerson;
    newPerson->next = NULL;

    return 0;
}

int deleteByLastName(position P, char lastName[MAX]) {
    // Pronadi element koji treba obrisati
    position element = searchByLastName(P, lastName);
    position q = P;

    if (element == NULL) {
        printf("Surname doesn't exist in list! \n");
    }
    else {
        // Pronadi element koji pokazuje na onaj koji brisemo
        while (q->next != element) {
            q = q->next;
        }
        // Prespoji obrisani element
        q->next = element->next;
        element->next = NULL;
        // Oslobodi memoriju
        free(element);
    }
    return 0;
}

position searchByLastName(position P, char lastName[MAX]) {
    // Kreni od pocetka i trazi podudaranje prezimena
    position q = P->next;
    while (q != NULL && strcmp(q->lastName, lastName) != 0) {
        q = q->next;
    }

    // Ako nije pronaden, vraca NULL
    if (q == NULL) {
        return NULL;
    }
    else {
        return q;
    }
}

int insertData(position newPerson, char firstName[MAX], char lastName[MAX], int birthYear) {
    // Kopiraj podatke u strukturu
    strcpy(newPerson->firstName, firstName);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;

    return 0;
}

int freeList(position P) {
    position temp = NULL;

    // Postupno oslobadja sve elemente liste
    while (P->next != NULL) {
        temp = P->next;
        P->next = temp->next;
        free(temp);
    }

    return 0;
}