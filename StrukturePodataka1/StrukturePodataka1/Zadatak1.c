#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 80


typedef struct {
	char firstName[MAX];
	char lastName[MAX];
	int points;
	double relPoints;

}stud;

int countLines(FILE*);
stud* allocateStudents(int, FILE*);
int calculateRelPoints(int, stud*);

int main() {
	int count;
	stud* s;
	int i; 

	FILE* input = fopen("Studenti.txt", "r");

	if (input == NULL) {
		printf("Greska pri otvaranju datoteke\n");
		exit(1);
	}

	count= countLines(input);
	rewind(input);
	
	s = allocateStudents(count, input);

	printf("Datoteka ima %d ucenika.\n\n", count);

	calculateRelPoints(count, s);

	printf("%-15s %-15s %-10s %-10s\n", "Ime", "Prezime", "Bodovi", "Relativni_bodovi\n");
	for (i = 0; i < count; i++)
			printf("%-15s %-15s %-10d %-10.2f\n", s[i].firstName, s[i].lastName, s[i].points, s[i].relPoints);
	fclose(input);
	free(s);
	return 0;
}


int countLines(FILE* file) {
	int counter= 0;
	int c;

	while (!feof(file)) {
		if (fgetc(file) == '\n')
			counter++;
	}
	return counter;
}

stud* allocateStudents(int n, FILE* file) {
	int i;
	stud* s;

	s = (stud*)malloc(n * sizeof(stud));
	if (!s) {
		printf("Greska pri alokaciji");
		exit(1);
	}
	for (i = 0; i < n; i++) {
		fscanf(file , "%s %s %d", s[i].firstName, s[i].lastName, & s[i].points);
	}
	return s;
}

int calculateRelPoints(int n, stud* students) {
	int maxPoints=0;
	int i;
	maxPoints = students[0].points;
	for (i = 1; i < n; i++) {
		if (students[i].points > maxPoints)
			maxPoints = students[i].points;
	}

	for (i = 0; i < n;i++) {
		students[i].relPoints = ((float)students[i].points/maxPoints) *100;
	}

	return 0;
}