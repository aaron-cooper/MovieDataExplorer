#include "name.h"


long int getNumActorEntries(char* fname)
{
    FILE* infile;
    char line[MAX_LINE_LEN];
    long int numFound = 0;
    char* pp = NULL; /*pp obviously stands for Primary Profession*/
    int ppLen = 0;

    infile = fopen(fname, "r");

    while (fgets(line, MAX_LINE_LEN, infile))
    {
        pp = cpycol(pp, line, &ppLen, 5, '\t');
        if (strstr(pp, "actor") || strstr(pp, "actress"))
        {
            numFound++;
        }
    }

    fclose(infile);

    if (pp != NULL)
    {
        free(pp);   
    }

    return numFound;
}


struct name_basics* constructNameBasicsArr(char* fname, int* arrLen)
{
    struct name_basics* newArr;
    FILE* infile;
    char line[MAX_LINE_LEN];
    int x = 0;
    char* pp = NULL;
    int ppLen = 0;

    *arrLen = getNumActorEntries(fname);
    newArr = malloc(sizeof(struct name_basics) * *arrLen);

    infile = fopen(fname, "r");

    while (fgets(line, MAX_LINE_LEN, infile))
    {
        pp = cpycol(pp, line, &ppLen, 5, '\t');
        if (strstr(pp, "actor") || strstr(pp, "actress"))
        {
            char* nconst = NULL;
            int nconstLen = 0;

            char* primaryName = NULL;
            int primaryNameLen = 0;

            nconst = cpycol(nconst, line, &nconstLen, 1, '\t');
            primaryName = cpycol(primaryName, line, &primaryNameLen, 2, '\t');
 
            newArr[x].nconst = nconst;
            newArr[x].primaryName = primaryName;

            x++;
        }
    }

    fclose(infile);

    if (pp != NULL)
    {
        free(pp);
    }

    return newArr;
}

void freeNameBasics(struct name_basics* arr, long int arrLen)
{
    int x;
    for (x = 0; x < arrLen; x++)
    {
        free(arr[x].nconst);
        free(arr[x].primaryName);
    }

    free(arr);

    return;
}

void printNB(void* toPrint)
{
    printf("%s, %s\n", ((struct name_basics*)(toPrint))->nconst,
        ((struct name_basics*)(toPrint))->primaryName);
    return;
}


int compareNamePrimaryName(const void* a, const void* b)
{
    return strcmp(((struct name_basics*)(a))->primaryName, ((struct name_basics*)(b))->primaryName);
}

int compareNameNConst(const void* a, const void* b)
{

    return strcmp(((struct name_basics*)(a))->nconst, ((struct name_basics*)(b))->nconst);
}


void* NBDeref(void* p)
{
    return *((struct name_basics**)(p));
}

int compareNBPptr(const void* a, const void* b)
{
    return compareNamePrimaryName(*((struct name_basics**)(a)), *((struct name_basics**)(b)));
}

int compareNBNptr (const void* a, const void* b)
{
    return compareNameNConst(*((struct name_basics**)(a)), *((struct name_basics**)(b)));
}