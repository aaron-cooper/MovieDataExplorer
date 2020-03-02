#ifndef PRINCIPALS_H
#define PRINCIPALS_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

struct title_principals {
    char *tconst;
    char *nconst;
    char *characters;
};

int getNumValidPrincipals(char* fname);

struct title_principals* constructTitlePrincipalsArr(char* fname, int *arrLen);

void freeTitlePrincipalsArr(struct title_principals* arr, int arrLen);

void printTP(void* toPrint);

int comparePrincipalsTConst(const void* a, const void* b);

int comparePrincipalsNConst(const void* a, const void* b);

void* TPDeref(void* p);

int comparePTCptr(const void* a, const void* b);


int comparePNCptr (const void* a, const void* b);


#endif