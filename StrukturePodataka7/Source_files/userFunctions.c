#define _CRT_SECURE_NO_WARNINGS
#include "../Header_files/treeFunctions.h"
#include "../Header_files/stackFunctions.h"
#include "../Header_files/userFunctions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Funkcija koja implementira korisnicki izbornik i upravlja radom programa 
int chooseOperations(Position dirP, Stack StackP) {
    int n;
    char name[40];  // spremnik za imena direktorija

    while (1) {
        printf("\nIzaberi operaciju:\n");
        printf("1 - md\n");
        printf("2 - cd\n");
        printf("3 - cd..\n");
        printf("4 - dir\n");
        printf("5 - rd /s dir\n");
        printf("6 - exit\n\n");
        printf("Izbor: ");

        scanf("%d", &n);   // ucitavanje korisnikovog izbora

        switch (n) {

        case 1:   // md - napravi direktorij u trenutnom direktoriju
            // dodaje novi poddirektorij u trenutni direktorij 
            printf("Ime direktorija: ");
            scanf("%s", name);
            makeDirectory(StackP, name);
            break;

        case 2:   // cd dir - odlazak u poddirektorij trenutnog direktorija
            // pronalazi poddirektorij po imenu i postavlja ga kao trenutni
            printf("Ime direktorija: ");
            scanf("%s", name);
            cdDirectory(StackP, name);
            break;

        case 3:   // cd.. - izlaz iz trenutnog direktorija
            // povratak u prethodni direktorij (pop sa stoga)
            pop(StackP);
            break;

        case 4:   // dir - ispisujemo imena poddirekorija trenutnog direktorija
            // ispisuje sadrzaj (poddirektorije) trenutnog direktorija
            printChildDirectories(StackP);
            break;

        case 5:   // rd /s dir - brisanje direktorija u trenutnom direktoriju
            // brise odabrani poddirektorij i sve njegove poddirektorije
            printf("Ime direktorija: ");
            scanf("%s", name);
            deleteDirectory(StackP->next->dir, name);
            break;

        case 6:   // exit - izlaz iz programa
            // prekida izvođenje programa i vraca kontrolu u main
            printf("Izlazak iz programa...\n");
            return EXIT_SUCCESS;

        default:
            // unos koji ne odgovara nijednoj opciji iz izbornika
            printf("Nevaljan odabir!\n");
        }
    }
}