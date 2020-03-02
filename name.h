#ifndef NAME_H
#define NAME_H

#include <stdio.h>
#include <string.h>
#include "common.h"


struct name_basics {
    char *nconst;
    char *primaryName;
};

/*
 * getNumActorEntries: counts the number of lines in a text file on which the 
 *  word "actor" appears
 * Param:
 *  char* fname: the name of the file to check
 * return: long int, the number of lines with the word "actor" on them
 */ 
long int getNumActorEntries(char* fname);

struct name_basics* constructNameBasicsArr(char* fname, int* arrLen);

void freeNameBasics(struct name_basics* arr, long int arrLen);

void printNB(void* toPrint);

int compareNamePrimaryName(const void* a, const void* b);

int compareNameNConst(const void* a, const void* b);

void* NBDeref(void* p);

int compareNBPptr(const void* a, const void* b);

int compareNBNptr (const void* a, const void* b);

#endif