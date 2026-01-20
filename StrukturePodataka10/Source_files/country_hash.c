#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERROR -1

#include "../Header_files/country_hash.h"
#include "../Header_files/io.h"

int hashIndexCountry(char name[]) {

	int i = 0;
	int sum = 0;

	for (i = 0; i < 5 && name[i] != '\0'; i++)
		sum += (int)name[i];



	return sum % SIZE;
}

int countryHashInsert(countryPosition hashTable[], countryPosition newCountry) {

	int index = hashIndexCountry(newCountry->name);
	countryPosition P = hashTable[index];
	hashTable[index] = countryListSortedInsert(P, newCountry);

	return SUCCESS;
}

countryPosition countryHashFind(countryPosition hashTable[], char name[]) {

	int index = hashIndexCountry(name);
	countryPosition P = hashTable[index];
	return countryListFind(P, name);
}

int countryHashPrint(countryPosition hashTable[]) {

	int i;
	for (i = 0; i < SIZE; i++) {
		printf("\n--BUCKET %d.--\n", i);
		if (hashTable[i])
			countryListPrint(hashTable[i]);
		else
			printf("Empty bucket!\n");
	}

	return SUCCESS;
}

int freeCountryHash(countryPosition hashTable[]) {

	int i;
	for (i = 0; i < SIZE; i++) {
		printf("Osloboden bucket %d.", i);
		freeCountryList(hashTable[i]);
		hashTable[i] = NULL;
	}
	return SUCCESS;
}

int createCountryHashCityTree(countryPosition hashTable[], char countriesFile[]) {

	FILE* file = NULL;
	char countryName[MAX_LINE];
	char cityNameFile[MAX_LINE];

	file = fopen(countriesFile, "r");
	if (!file) {
		printf("Cannot open countries file!\n");
		return ERROR;
	}

	while (fscanf(file, "%s %s", countryName, cityNameFile) == 2) {
		countryPosition newCountry = countryInitialize(countryName, cityNameFile);

		if (!newCountry) {
			fclose(file);
			return ERROR;
		}

		newCountry->cityRoot = loadCitiesTree(cityNameFile);

		countryHashInsert(hashTable, newCountry);
	}

	fclose(file);
	return SUCCESS;
}