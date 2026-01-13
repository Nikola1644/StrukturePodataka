#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Header_files/city.h"
#include "../Header_files/country.h"
#include "../Header_files/io.h"

#define SUCCESS 0
#define ERROR -1

int trimNewline(char s[])
{
    int lenght;
    if (!s) return ERROR;

    lenght = strlen(s);
    if (lenght > 0 && (s[lenght - 1] == '\n' || s[lenght - 1] == '\r'))
        s[lenght - 1] = '\0';

    lenght = strlen(s);
    if (lenght > 0 && s[lenght - 1] == '\r')
        s[lenght - 1] = '\0';

    return SUCCESS;
}

int trimSpaces(char s[])
{
    int start = 0;
    int end;
    int i, j = 0;

    if (!s) return ERROR;

    end = strlen(s) - 1;

    while (s[start] == ' ' || s[start] == '\t')
        start++;

    while (end >= start && (s[end] == ' ' || s[end] == '\t'))
        end--;

    for (i = start; i <= end; i++)
        s[j++] = s[i];

    s[j] = '\0';
    return SUCCESS;
}
int parseCityLine(char line[], char name[], int* pop)
{
    char* comma;

    comma = strchr(line, ',');
    if (!comma) return ERROR;

    *comma = '\0';
    strcpy(name, line);
    trimSpaces(name);

    comma++;
    trimSpaces(comma);

    if (sscanf(comma, "%d", pop) != 1)
        return ERROR;

    return SUCCESS;
}
cityPosition loadCitiesTree(char citiesFile[])
{
    FILE* f;
    char line[100];
    cityPosition root = NULL;

    if (!citiesFile) return NULL;

    f = fopen(citiesFile, "r");
    if (!f) return NULL;

    while (fgets(line, 100, f)) {
        char name[64];
        int pop;
        cityPosition c;

        trimNewline(line);
        if (strlen(line) == 0) continue;

        if (parseCityLine(line, name, &pop) != SUCCESS)
            continue;

        c = cityInitialize(name, pop);
        if (!c) {
            fclose(f);
            freeCityTree(root);
            return NULL;
        }

        root = cityTreeSortedInsert(root, c);
    }

    fclose(f);
    return root;
}


cityPosition loadCitiesList(char citiesFile[])
{
    FILE* f;
    char line[100];
    cityPosition head = NULL;

    if (!citiesFile) return NULL;

    f = fopen(citiesFile, "r");
    if (!f) return NULL;

    while (fgets(line, 100, f)) {
        char name[64];
        int pop;
        cityPosition c;

        trimNewline(line);
        if (strlen(line) == 0) continue;

        if (parseCityLine(line, name, &pop) != SUCCESS)
            continue;

        c = cityInitialize(name, pop);
        if (!c) {
            fclose(f);
            freeCityList(head);  
            return NULL;
        }

        head = cityListSortedInsert(head, c);
    }

    fclose(f);
    return head;
}


countryPosition createCountryListCityTree(char countriesFile[])
{
    FILE* f;
    char line[100];
    countryPosition head = NULL;

    if (!countriesFile) return NULL;

    f = fopen(countriesFile, "r");
    if (!f) return NULL;

    while (fgets(line, 100, f)) {
        char cname[70];
        char cfile[100];
        countryPosition c;

        trimNewline(line);
        if (strlen(line) == 0) continue;

        if (sscanf(line, "%70s %100s", cname, cfile) != 2) // ako nije procitao oba
            continue;

        c = countryInitialize(cname, cfile);
        if (!c) {
            fclose(f);
            freeCountryList(head);
            return NULL;
        }

        c->cityRoot = loadCitiesTree(c->cityNameFile);
        c->cityP = NULL;

        head = countryListSortedInsert(head, c);
    }

    fclose(f);
    return head;
}

countryPosition createCountryTreeCityList(char countriesFile[])
{
    FILE* f;
    char line[100];
    countryPosition root = NULL;

    if (!countriesFile) return NULL;

    f = fopen(countriesFile, "r");
    if (!f) return NULL;

    while (fgets(line, 100, f)) {
        char cname[70];
        char cfile[100];
        countryPosition c;

        trimNewline(line);
        if (strlen(line) == 0) continue;

        if (sscanf(line, "%70s %100s", cname, cfile) != 2)
            continue;

        c = countryInitialize(cname, cfile);
        if (!c) {
            fclose(f);
            freeCountryTree(root);
            return NULL;
        }

        c->cityP = loadCitiesList(c->cityNameFile);
        c->cityRoot = NULL;

        root = countryTreeSortedInsert(root, c);
    }

    fclose(f);
    return root;
}