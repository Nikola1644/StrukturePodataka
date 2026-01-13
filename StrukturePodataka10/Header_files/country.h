#ifndef COUNTRY_H
#define COUNTRY_H

#include "city.h"

typedef struct country* countryPosition;
typedef struct country {
	char name[50];
	char cityNameFile[100]; //ime datoteke sa gradovima

	cityPosition cityRoot;
	cityPosition cityP;

	countryPosition nextCountry;
	countryPosition leftCountry, rightCountry;

}country;

int countryNameCompare(char a[], char b[]);
countryPosition countryInitialize(char name[], char cityNameFile[]);

countryPosition countryListSortedInsert(countryPosition P, countryPosition newCountry);
int countryListPrint(countryPosition P);
countryPosition countryListFind(countryPosition P, char name[]);

countryPosition countryTreeSortedInsert(countryPosition root, countryPosition newCountry);
int countryTreePrintInOrder(countryPosition root);
countryPosition countryTreeFind(countryPosition root, char name[]);

int freeCountryList(countryPosition P);
int freeCountryTree(countryPosition root);

#endif


