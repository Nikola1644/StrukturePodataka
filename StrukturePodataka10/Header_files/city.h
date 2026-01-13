#ifndef CITY_H
#define CITY_H
typedef struct city* cityPosition;
typedef struct city {
	char name[50];
	int population;
	cityPosition nextCity;
	cityPosition rightCity, leftCity;

}city;

cityPosition cityInitialize(char name[], int population);
int cityCompare(cityPosition city1, cityPosition city2);

cityPosition cityListSortedInsert(cityPosition P, cityPosition newCity);
int cityListPrint(cityPosition P);
int cityListPrintHigher(cityPosition P, int min);

cityPosition cityTreeSortedInsert(cityPosition root, cityPosition newCity);
int cityTreePrintInOrder(cityPosition root);
int cityTreePrintHigher(cityPosition root, int min);


int freeCityList(cityPosition P);
int freeCityTree(cityPosition root);

#endif