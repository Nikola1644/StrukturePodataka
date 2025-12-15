#define _CRT_SECURE_NO_WARNINGS
#include "../Header_files/treeFunctions.h"
#include "../Header_files/stackFunctions.h"
#include "../Header_files/userFunctions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Glavna funkcija programa 
int main() {

    // Inicijalizacija root direktorija (pocetni direktorij C:) 
    Position root = directoryInitialize("C:");

    // Inicijalizacija stoga za pracenje trenutnog direktorija 
    Stack stackHead = stackInitialize(NULL);

    // Postavljanje root direktorija kao trenutnog direktorija 
    push(stackHead, root);

    // Pokretanje korisnickog sucelja (meni s DOS naredbama) 
    chooseOperations(root, stackHead);

    // Oslobadanje memorije zauzete stablom direktorija 
    freeTree(root);

    // Oslobadanje memorije zauzete stogom 
    freeStack(stackHead);

    return EXIT_SUCCESS;
}