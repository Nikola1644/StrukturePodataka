#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Header_files/city.h"

#define SUCCESS 0
#define ERROR -1

cityPosition cityInitialize(char name[], int population) {

	cityPosition newCity = (cityPosition)malloc(sizeof(city));
	if (!newCity)
		return NULL;
	strcpy(newCity->name, name);
	newCity->population = population;

	newCity->nextCity = NULL;
	newCity->leftCity = NULL;
	newCity->rightCity = NULL;

	return newCity;
}

int cityCompare(cityPosition city1, cityPosition city2) {

	if (!city1 || !city2)
		return 0;
	if (city1->population != city2->population)
		return(city2->population - city1->population);
	return strcmp(city1->name, city2->name);
}

cityPosition cityListSortedInsert(cityPosition P, cityPosition newCity) {
	if (!newCity)
		return P;
	if (!P || cityCompare(newCity, P) < 0) {
		newCity->nextCity = P;
		return newCity;
	}

	cityPosition prev = P;
	cityPosition cur = P->nextCity;

	while (cur && cityCompare(newCity, cur) >= 0) {
		prev = cur;
		cur = cur->nextCity;
	}

	newCity->nextCity = cur;
	prev->nextCity = newCity;
	return P;
}

int cityListPrint(cityPosition P) {
	while (P) {
		printf("    %s, %d\n", P->name, P->population);
		P = P->nextCity;
	}
	return SUCCESS;
}

int cityListPrintHigher(cityPosition P, int min) {
	while (P) {
		if(P->population>min)
			printf("    %s, %d\n", P->name, P->population);
		P = P->nextCity;
	}
	return SUCCESS;
}

cityPosition cityTreeSortedInsert(cityPosition root, cityPosition newCity) {
	if (!newCity)
		return root;
	if (!root)
		return newCity;
	if (cityCompare(newCity, root) < 0)
		root->leftCity = cityTreeSortedInsert(root->leftCity, newCity);
	else
		root->rightCity = cityTreeSortedInsert(root->rightCity, newCity);

	return root;
}

int cityTreePrintInOrder(cityPosition root) {
	if (!root) return SUCCESS;

	cityTreePrintInOrder(root->leftCity);
	printf("    %s, %d\n", root->name, root->population);
	cityTreePrintInOrder(root->rightCity);

	return SUCCESS;
}
int cityTreePrintHigher(cityPosition root, int min)
{
	if (!root) return SUCCESS;
	
	cityTreePrintHigher(root->leftCity, min);
	if (root->population > min)
		printf("    %s, %d\n", root->name, root->population);
	cityTreePrintHigher(root->rightCity, min);

	return SUCCESS;
}

int freeCityList(cityPosition P)
{
	while (P) {
		cityPosition tmp = P;
		P = P->nextCity;
		free(tmp);
	}
	return SUCCESS;
}

int freeCityTree(cityPosition root)
{
	if (!root) return SUCCESS;

	freeCityTree(root->leftCity);
	freeCityTree(root->rightCity);
	free(root);

	return SUCCESS;
}