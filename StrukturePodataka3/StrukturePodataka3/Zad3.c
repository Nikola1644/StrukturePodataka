#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SUCCESS 0
#define ERROR -1
#define MAX 40

// Definicija strukture i pokazivaca na strukturu
typedef struct person* position;
typedef struct person {
    char firstName[MAX];
    char lastName[MAX];
    int birthYear;
    position next;
} person;

// Deklaracije funkcija
int insertStartPerson(position P);
int insertEndPerson(position P);
int deleteByLastName(position P);
position searchByLastName(position P, char lastName[MAX]);
int printList(position P);
int insertAfter(position P);
int insertBefore(position P);
int insertData(position newPerson);
int freeList(position P);
int writeInFile(position P);
int readFromFile(position P);
int sortList(position P);

int main() {
    // Kreiramo prazan cvor koji sluzi kao glava liste (ne sadrzi stvarne podatke)
    struct person head = { .firstName = "", .lastName = "", .birthYear = 0, .next = NULL };
    position P = &head;
    int n;
    int radi = 1;

    // UI za odabir funkcije za izvrsavanje
    printf("Izaberi funckiju:\n");
    printf("1->Dodaj na pocetak\n2->Dodaj na kraj\n3->Ispisi listu\n4->Obrisi po prezimenu\n5->Ubaci iza elementa\n");
    printf("6->Ubaci ispred elementa\n7->Upisi u datoteku\n8->Citaj iz datoteke\n9->Sortiraj listu\n10->Izlaz iz programa\n\n");
    while (radi) {
        scanf("%d", &n);

        switch (n) {
        case 1:
            insertStartPerson(P);
            break;
        case 2:
            insertEndPerson(P);
            break;
        case 3:
            printList(P);
            break;
        case 4:
            deleteByLastName(P);
            break;
        case 5:
            insertAfter(P);
            break;
        case 6:
            insertBefore(P);
            break;
        case 7:
            writeInFile(P);
            break;
        case 8:
            readFromFile(P);
            break;
        case 9:
            sortList(P);
            break;
        case 10:
            radi = 0;
            break;
        default:
            printf("Unesen krivi broj!\n");
            break;
        }
    }

    // Oslobadamo alocirani prostor
    freeList(P);
    return 0;
}

int insertStartPerson(position P) {
    // Dodaje novi element na pocetak liste
    position newPerson = (position)malloc(sizeof(person));
    if (newPerson == NULL) {
        printf("Greska alokacije!\n");
        return -1;
    }

    insertData(newPerson);  // Unos podataka za novi element
    newPerson->next = P->next;  // Novi element pokazuje na stari prvi
    P->next = newPerson;  // Head pokazuje na novi element

    printf("Osoba dodana na pocetak liste!\n");

    return 0;
}

int printList(position P) {
    if (P->next == NULL) {
        printf("Lista je prazna!\n");
        return 0;
    }
    // Ispisuje sve elemente liste
    position q = P->next;
    while (q != NULL) {
        printf("%s %s %d \n", q->firstName, q->lastName, q->birthYear);
        q = q->next;
    }
    return 0;
}

int insertEndPerson(position P) {
    // Dodaje novi element na kraj liste
    position newPerson = (position)malloc(sizeof(person));
    if (newPerson == NULL) {
        printf("Greska alokacije!\n");
        return -1;
    }

    // Pronadi kraj liste
    position q = P;
    while (q->next != NULL)
        q = q->next;

    insertData(newPerson);  // Unesi podatke u novi element
    newPerson->next = NULL;
    q->next = newPerson;    // Spoji na kraj

    printf("Osoba dodana na kraj liste!\n");

    return 0;
}

int deleteByLastName(position P) {
    // Brise osobu iz liste prema prezimenu
    char ln[MAX];
    printf("Unesi prezime za brisanje: ");
    scanf("%s", ln);

    position element = searchByLastName(P, ln);
    position q = P;

    if (element == NULL) {
        printf("Prezime ne postoji u listi! \n");
    }
    else {
        // Pronadi prethodni element
        while (q->next != element)
            q = q->next;

        q->next = element->next; // Preskoci obrisani
        free(element);    // Oslobodi memoriju

        printf("Osoba obrisana iz liste!\n");
    }

    return 0;
}

position searchByLastName(position P, char lastName[MAX]) {
    // Trazi osobu prema prezimenu
    position q = P->next;
    while (q != NULL && strcmp(q->lastName, lastName) != 0)
        q = q->next;

    return q; // Vraca NULL ako nije pronadena
}

int insertAfter(position P) {
    // Ubacuje novi element iza trazenog prezimena
    char findLastName[MAX];
    printf("Unesi prezime za ubacivanje iza njega: ");
    scanf("%s", findLastName);

    position q = searchByLastName(P, findLastName);
    if (q == NULL) {
        printf("Prezime nije pronadeno!\n");
        return -1;
    }

    position newPerson = (position)malloc(sizeof(person));
    if (newPerson == NULL) {
        printf("Greska alokacije!\n");
        return -1;
    }

    insertData(newPerson);   // Unesi nove podatke
    newPerson->next = q->next;
    q->next = newPerson;     // Spoji iza trazenog

    printf("Osoba unesena u listu!\n");

    return 0;
}

int insertBefore(position P) {
    // Ubacuje novi element ispred trazenog prezimena
    char findLastName[MAX];
    printf("Unesi prezime za ubacivanje ispred njega: ");
    scanf("%s", findLastName);

    position prev = P;
    position q = P->next;

    // Pronadi element ispred trazenog
    while (q != NULL && strcmp(q->lastName, findLastName) != 0) {
        prev = q;
        q = q->next;
    }

    if (q == NULL) {
        printf("Prezime ne postoji u listi!\n");
        return -1;
    }

    position newPerson = (position)malloc(sizeof(person));
    if (newPerson == NULL) {
        printf("Greska alokacije!\n");
        return -1;
    }

    insertData(newPerson); // Unesi podatke

    newPerson->next = q;   // Novi pokazuje na stari
    prev->next = newPerson;

    printf("Osoba unesena u listu!\n");

    return 0;
}

int writeInFile(position P) {
    // Upisuje sve osobe iz liste u tekstualnu datoteku
    FILE* dat = fopen("lista.txt", "w");
    if (dat == NULL) {
        printf("Datoteka nije otvorena!\n");
        return -1;
    }

    for (position q = P->next; q != NULL; q = q->next)
        fprintf(dat, "%s %s %d\n", q->firstName, q->lastName, q->birthYear);

    fclose(dat);
    printf("Podatci upisani u datoteku!\n");

    return 0;
}

int readFromFile(position P) {
    // Ucitava osobe iz tekstualne datoteke u listu
    char firstName[MAX], lastName[MAX];
    int birthYear = 0;

    FILE* dat = fopen("lista.txt", "r");
    if (dat == NULL) {
        printf("Datoteka nije otvorena!\n");
        return -1;
    }

    // Postavi q na kraj liste
    position q = P;
    while (q->next != NULL)
        q = q->next;

    // Cita podatke dok fscanf vraca 3 uspjesno ucitana elementa
    while (fscanf(dat, "%s %s %d", firstName, lastName, &birthYear) == 3) {
        position newPerson = (position)malloc(sizeof(person));
        if (newPerson == NULL) {
            printf("Greska alokacije!\n");
            fclose(dat);
            return -1;
        }

        strcpy(newPerson->firstName, firstName);
        strcpy(newPerson->lastName, lastName);
        newPerson->birthYear = birthYear;
        newPerson->next = NULL;

        q->next = newPerson; // Dodaj na kraj
        q = newPerson;
    }

    fclose(dat);
    printf("Podatci procitani iz datoteke!\n");
    return 0;
}

int sortList(position P) {
    // Sortira listu po prezimenu (bubble sort)
    position q, tmp, prev, end = NULL;

    while (P->next != end) {
        prev = P;
        q = P->next;
        while (q->next != end) {
            // Usporedi prezimena
            if (strcmp(q->lastName, q->next->lastName) > 0) {
                // Zamijeni elemente
                tmp = q->next;
                prev->next = tmp;
                q->next = tmp->next;
                tmp->next = q;
                q = tmp;
            }
            prev = q;
            q = q->next;
        }
        end = q; // Oznaci kraj sortirane sekcije
    }

    printf("Lista sortirana po prezimenu.\n");
    return 0;
}

int insertData(position newPerson) {
    // Unosi podatke o osobi s tipkovnice
    int by;
    char fn[MAX], ln[MAX];

    printf("First name: ");
    scanf("%s", fn);
    printf("Last name: ");
    scanf("%s", ln);
    printf("Birth year: ");
    scanf("%d", &by);

    strcpy(newPerson->firstName, fn);
    strcpy(newPerson->lastName, ln);
    newPerson->birthYear = by;

    return 0;
}

int freeList(position P) {
    // Oslobadja memoriju svih elemenata liste osim glave
    position q = NULL;

    while (P->next != NULL) {
        q = P->next;
        P->next = q->next;
        free(q);
    }
    return 0;
}