/* Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
   rezultat. Stog je potrebno realizirati preko vezane liste.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define SUCCESS 1
#define ERROR -1

// Definicija strukture koja predstavlja jedan element stoga
typedef struct number* position;
typedef struct number {
	double numb;     // Vrijednost broja
	position next;   // Pokazivač na sljedeći element u stogu
} number;

// Deklaracije funkcija
position initialize();
int pop(position head);
int push(position head, double numb);
int calculate(position head, char buffer);
int readFromFile(position head);
int printResult(position head);
int clearStack(position head);

int main() {
	position head = initialize();   // Inicijalizacija glave stoga (prazan stog)
	readFromFile(head);             // Čitanje postfix izraza iz datoteke i računanje
	printResult(head);              // Ispis rezultata izraza
	clearStack(head);               // Oslobađanje zauzete memorije

	return 0;
}

// Funkcija za inicijalizaciju novog elementa (glave)
position initialize() {
	position newElem = (position)malloc(sizeof(number));
	if (newElem == NULL) {         // Provjera alokacije memorije
		printf("Allocation error!\n");
		return NULL;
	}
	else {
		newElem->numb = 0;
		newElem->next = NULL;
		return newElem;
	}
}

// Dodavanje novog elementa (broja) na vrh stoga
int push(position head, double numb) {
	position newElem = initialize();
	if (newElem == NULL)
		return ERROR;

	newElem->numb = numb;       // Postavljanje vrijednosti novog elementa
	newElem->next = head->next; // Novi element pokazuje na prethodni vrh stoga
	head->next = newElem;       // Glava pokazuje na novi element

	return SUCCESS;
}

// Uklanjanje elementa s vrha stoga
int pop(position head) {
	position temp = head->next;
	if (temp == NULL) {        // Ako je stog prazan
		printf("The stack is empty!\n");
		return ERROR;
	}

	head->next = temp->next;   // Pomicanje vrha stoga
	temp->next = NULL;
	free(temp);                // Oslobađanje memorije za obrisani element

	return SUCCESS;
}

// Funkcija koja čita postfix izraz iz datoteke i izvršava odgovarajuće operacije
int readFromFile(position head) {
	FILE* data = fopen("data.txt", "r");
	if (data == NULL) {
		printf("File opening error!\n");
		exit(ERROR);
	}

	// Provjera je li datoteka prazna
	if (fgetc(data) == EOF) {
		printf("File is empty!\n");
		exit(ERROR);
	}
	rewind(data);  // Vraća pokazivač datoteke na početak

	char buffer[100];  // Buffer za čitanje svakog tokena iz datoteke

	// Čitanje tokena jedan po jedan (brojevi ili operatori)
	while (fscanf(data, "%s", buffer) != EOF) {
		// Ako token predstavlja broj (pozitivan ili negativan)
		if (buffer[0] == '-' && isdigit(buffer[1]) || isdigit(buffer[0])) {
			double br = atof(buffer);   // Pretvara string u double
			push(head, br);             // Gura broj na stog
		}
		else {
			// Ako nema dovoljno operanada na stogu
			if (head->next == NULL) {
				printf("Postfix not correct!\n");
				return ERROR;
			}
			// Ako je token operator (+, -, *, /)
			else if (strlen(buffer) == 1 && strchr("+-*/", buffer[0]))
				calculate(head, buffer[0]);
			else {
				// Ako se u izrazu pojavi nepoznati znak
				printf("Invalid character in postfix!\n");
			}
		}
	}
	fclose(data);
	return SUCCESS;
}

// Funkcija koja izvršava aritmetičku operaciju nad zadnja dva broja sa stoga
int calculate(position head, char buffer) {
	position temp = head->next;
	if (temp == NULL || temp->next == NULL) {
		printf("Not enough operands found!\n");
		exit(ERROR);
	}

	// Operator određuje koju operaciju treba izvršiti
	switch (buffer) {
	case '-':
		temp->next->numb = temp->next->numb - temp->numb;
		pop(head);  // Uklanja operand koji je već iskorišten
		break;
	case '+':
		temp->next->numb = temp->next->numb + temp->numb;
		pop(head);
		break;
	case '*':
		temp->next->numb = temp->next->numb * temp->numb;
		pop(head);
		break;
	case '/':
		// Provjera dijeljenja s nulom
		if (temp->numb == 0) {
			printf("Not possible to devide with 0!\n");
			exit(ERROR);
		}
		else {
			temp->next->numb = temp->next->numb / temp->numb;
			pop(head);
			break;
		}
	default:
		printf("Invalid operator!\n");
		exit(ERROR);
	}
	return SUCCESS;
}

// Funkcija koja ispisuje rezultat na ekranu
int printResult(position head) {
	position temp = head->next;
	if (temp == NULL) {
		printf("Stack is empty!\n");
		return ERROR;
	}
	// Ako nakon računanja u stogu ostane više od jednog broja, izraz nije ispravan
	if (temp->next != NULL) {
		printf("Too many operands in postfix!\n");
		return ERROR;
	}

	printf("The result is: %.2f\n", temp->numb);
	return SUCCESS;
}

// Funkcija koja oslobađa svu memoriju povezane liste
int clearStack(position head) {
	while (head) {
		position temp = head;
		head = head->next;
		free(temp);
	}
	return SUCCESS;
}