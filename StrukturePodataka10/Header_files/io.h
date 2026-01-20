#ifndef IO_H
#define IO_H
#define MAX_LINE 256
#include "country.h"
#include "city.h"

int trimNewline(char s[]);
int trimSpaces(char s[]);
int parseCityLine(char line[], char name[], int* pop);


countryPosition createCountryListCityTree(char countriesFile[]);
countryPosition createCountryTreeCityList(char countriesFile[]);

cityPosition loadCitiesTree(char citiesFile[]);
cityPosition loadCitiesList(char citiesFile[]);

#endif