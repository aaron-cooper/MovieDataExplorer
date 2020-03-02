#ifndef TITLE_H
#define TITLE_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

struct title_basics {
    char *tconst;
    char *primaryTitle;
};


int getNumValidTitleBasics(char* fname);


struct title_basics* constructTitleBasicsArr(char* fname, int* arrLen);


void freeTitleBasics(struct title_basics* arr, int arrLen);

int compareTitleTConst(const void* a, const void* b);

int compareTitlePrimaryTitle(const void* a, const void* b);

void* TBDeref(void* p);

int compareTTCptr(const void* a, const void* b);

int compareTPTptr (const void* a, const void* b);

#endif