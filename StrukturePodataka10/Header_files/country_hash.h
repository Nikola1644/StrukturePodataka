#ifndef COUNTRY_HASH_H
#define COUNTRY_HASH_H
#include "country.h"
#define SIZE 11

int hashIndexCountry(char name[]);
int createCountryHashCityTree(countryPosition hashTable[], char countriesFile[]);
int countryHashInsert(countryPosition hashTable[], countryPosition newCountry);
countryPosition countryHashFind(countryPosition hashTable[], char name[]);
int countryHashPrint(countryPosition hashTable[]);
int freeCountryHash(countryPosition hashTable[]);

#endif