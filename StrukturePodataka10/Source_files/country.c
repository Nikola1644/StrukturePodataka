#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Header_files/city.h"
#include "../Header_files/country.h"

#define SUCCESS 0
#define ERROR -1

int countryNameCompare(char a[], char b[]) {
	if (strcmp(a, b) == 0)
		return 0;
	else
		return strcmp(a, b);
}

countryPosition countryInitialize(char name[], char cityNameFile[]) {
	countryPosition newCountry = (countryPosition)malloc(sizeof(country));
	if (!newCountry)
		return NULL;

	strcpy(newCountry->name, name);
	strcpy(newCountry->cityNameFile, cityNameFile);

	newCountry->cityRoot = NULL;
	newCountry->cityP = NULL;

	newCountry->nextCountry = NULL;
	newCountry->leftCountry = NULL;
	newCountry->rightCountry = NULL;

	return newCountry;
}
countryPosition countryListSortedInsert(countryPosition P, countryPosition newCountry) {
	if (!newCountry)
		return P;

	if (!P || countryNameCompare(newCountry->name, P->name) < 0) {
		newCountry->nextCountry = P;
		return newCountry;
	}

	countryPosition prev = P;
	countryPosition curr = P->nextCountry;

	while (curr && countryNameCompare(newCountry->name, curr->name)) {
		prev = curr;
		curr = curr->nextCountry;

	}
	newCountry->nextCountry = curr;
	prev->nextCountry = newCountry;

	return P;
}

int countryListPrint(countryPosition P) {
	while (P) {
		printf("%s\n", P->name);
		if (P->cityRoot)
			cityTreePrintInOrder(P->cityRoot);
		else if (P->cityP)
			cityListPrint(P->cityP);
		P = P->nextCountry;
	}
	return SUCCESS;
}

countryPosition countryListFind(countryPosition P, char name[]) {

	while (P) {
		if (countryNameCompare(name, P->name) == 0)
			return P;
		if (countryNameCompare(name, P->name) < 0)
			return NULL;
		P = P->nextCountry;
	}
	return NULL;
}

countryPosition countryTreeSortedInsert(countryPosition root, countryPosition newCountry) {
	if (!newCountry)
		return root;
	else if (!root)
		return newCountry;

	if (countryNameCompare(newCountry->name, root->name) < 0)
		root->leftCountry = countryTreeSortedInsert(root->leftCountry, newCountry);
	else
		root->rightCountry = countryTreeSortedInsert(root->rightCountry, newCountry);

	return root;
}

int countryTreePrintInOrder(countryPosition root) {
	if (!root)
		return SUCCESS;

	countryTreePrintInOrder(root->leftCountry);
	printf("%s\n", root->name);
	if (root->cityRoot) cityTreePrintInOrder(root->cityRoot);
	else if (root->cityP) cityListPrint(root->cityP);
	countryTreePrintInOrder(root->rightCountry);

	return SUCCESS;
}

countryPosition countryTreeFind(countryPosition root, char name[]) {
	while (root) {
		if (countryNameCompare(name, root->name)== 0) return root;
		if (countryNameCompare(name, root->name)<0) root = root->leftCountry;
		else root = root->rightCountry;
	}
	return NULL;
}

int freeCountryList(countryPosition P)
{
	while (P) {
		countryPosition tmp = P;
		P = P->nextCountry;

		if (tmp->cityRoot) freeCityTree(tmp->cityRoot);
		if (tmp->cityP) freeCityList(tmp->cityP);

		free(tmp);
	}
	return SUCCESS;
}

int freeCountryTree(countryPosition root)
{
	if (!root) return SUCCESS;

	freeCountryTree(root->leftCountry);
	freeCountryTree(root->rightCountry);

	if (root->cityRoot) freeCityTree(root->cityRoot);
	if (root->cityP) freeCityList(root->cityP);

	free(root);
	return SUCCESS;
}