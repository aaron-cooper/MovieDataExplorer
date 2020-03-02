
#include "title.h"

int getNumValidTitleBasics(char* fname)
{
    FILE* infile = NULL;
    char line[MAX_LINE_LEN];
    int numFound = 0;
    char* titleType = NULL;
    int titleTypeLen = 0;
    char* isAdult = NULL;
    int isAdultLen = 0;


    infile = fopen (fname, "r");

    while(fgets(line, MAX_LINE_LEN, infile))
    {
        titleType = cpycol(titleType, line, &titleTypeLen, 2, '\t');
        isAdult = cpycol(isAdult, line, &isAdultLen, 5, '\t');

        if (strstr(titleType, "movie") && strstr(isAdult, "0"))
        {
            numFound++;
        }
    }

    fclose(infile);

    if (titleType != NULL)
    {
        free(titleType);
    }
    if (isAdult != NULL)
    {
        free(isAdult);
    }
    
    return numFound;
}



struct title_basics* constructTitleBasicsArr(char* fname, int* arrLen)
{
    struct title_basics* newArr;
    FILE* infile;
    char line[MAX_LINE_LEN];
    int x = 0;
    char* titleType = NULL;
    int titleTypeLen = 0;
    char* isAdult = NULL;
    int isAdultLen = 0;

    *arrLen = getNumValidTitleBasics(fname);
    newArr = malloc(sizeof(struct title_basics) * *arrLen);

    infile = fopen (fname, "r");

    while(fgets(line, MAX_LINE_LEN, infile))
    {
        titleType = cpycol(titleType, line, &titleTypeLen, 2, '\t');
        isAdult = cpycol(isAdult, line, &isAdultLen, 5, '\t');

        if (strstr(titleType, "movie") && strstr(isAdult, "0"))
        {
            char* tconst = NULL;
            int tconstLen = 0;

            char* primaryTitle = NULL;
            int primaryTitleLen = 0;

            tconst = cpycol(tconst, line, &tconstLen, 1, '\t');
            primaryTitle = cpycol(primaryTitle, line, &primaryTitleLen, 3, '\t');

            newArr[x].tconst = tconst;
            newArr[x].primaryTitle = primaryTitle;

            x++;
        }
    }

    fclose(infile);

    if (titleType)
    {
        free(titleType);
    }

    if(isAdult)
    {
        free(isAdult);
    }
    

    return newArr;
}

void freeTitleBasics(struct title_basics* arr, int arrLen)
{
    int x;
    for (x = 0; x < arrLen; x++)
    {
        free(arr[x].primaryTitle);
        free(arr[x].tconst);
    }
    free (arr);
}



int compareTitleTConst(const void* a, const void* b)
{
    return strcmp (((struct title_basics*)(a))->tconst, ((struct title_basics*)(b))->tconst);
}

int compareTitlePrimaryTitle(const void* a, const void* b)
{
    return strcmp (((struct title_basics*)(a))->primaryTitle, ((struct title_basics*)(b))->primaryTitle);
}

void* TBDeref(void* p)
{
    return *((struct title_basics**)(p));
}

int compareTTCptr(const void* a, const void* b)
{
    return compareTitleTConst(*((struct title_basics**)(a)), *((struct title_basics**)(b)));
}

int compareTPTptr (const void* a, const void* b)
{
    return compareTitlePrimaryTitle(*((struct title_basics**)(a)), *((struct title_basics**)(b)));
}