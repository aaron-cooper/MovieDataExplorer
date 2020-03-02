#include "principals.h"


int getNumValidPrincipals(char* fname)
{
    FILE* infile = NULL;
    int numFound = 0;
    char line[MAX_LINE_LEN];

    char* category = NULL;
    int categoryLen = 0;

    infile = fopen(fname, "r");

    while(fgets(line, MAX_LINE_LEN, infile))
    {
        category = cpycol(category, line, &categoryLen, 4, '\t');
        if (strstr(category, "actor") || strstr(category, "actress"))
        {
            numFound++;
        }
    }

    fclose(infile);

    if (category != NULL)
    {
        free(category);
    }

    return numFound;
}


struct title_principals* constructTitlePrincipalsArr(char* fname, int *arrLen)
{
    struct title_principals* newArr;
    FILE* infile;
    char line[MAX_LINE_LEN];
    int x = 0;
    char* category = NULL;
    int categoryLen= 0;
    
    *arrLen = getNumValidPrincipals(fname);
    newArr = malloc(sizeof(struct title_principals) * *arrLen);

    infile = fopen(fname, "r");

    while (fgets(line, MAX_LINE_LEN, infile))
    {
        category = cpycol(category, line, &categoryLen, 4, '\t');
        if (strstr(category, "actor") || strstr(category, "actress"))
        {
            char* tconst = NULL;
            int tconstLen = 0;

            char* nconst = NULL;
            int nconstLen = 0;

            char* characters = NULL;
            int charactersLen = 0;


            tconst = cpycol(tconst, line, &tconstLen, 1, '\t');
            nconst = cpycol(nconst, line, &nconstLen, 3, '\t');
            characters = cpycol(characters, line, &charactersLen, 6, '\t');
 
            newArr[x].nconst = nconst;
            newArr[x].tconst = tconst;
            newArr[x].characters = characters;

            x++;
        }
    }

    fclose(infile);

    if (category != NULL)
    {
        free(category);
    }

    return newArr;
}


void freeTitlePrincipalsArr(struct title_principals* arr, int arrLen)
{
    int x;

    for (x = 0; x < arrLen; x++)
    {
        free(arr[x].characters);
        free(arr[x].nconst);
        free(arr[x].tconst);
    }
    free(arr);
}

void printTP(void* toPrint)
{
    printf("%s, %s, %s\n", ((struct title_principals*)(toPrint))->tconst,
        ((struct title_principals*)(toPrint))->nconst,
        ((struct title_principals*)(toPrint))->characters);
    return;
}


int comparePrincipalsTConst(const void* a, const void* b)
{
    return strcmp (((struct title_principals*)(a))->tconst, ((struct title_principals*)(b))->tconst);
}

int comparePrincipalsNConst(const void* a, const void* b)
{
    return strcmp (((struct title_principals*)(a))->nconst, ((struct title_principals*)(b))->nconst);
}

void* TPDeref(void* p)
{
    return *((struct title_principals**)(p));
}

int comparePTCptr(const void* a, const void* b)
{
    return comparePrincipalsTConst(*((struct title_principals**)(a)), *((struct title_principals**)(b)));
}

int comparePNCptr (const void* a, const void* b)
{
    return comparePrincipalsNConst(*((struct title_principals**)(a)), *((struct title_principals**)(b)));
}