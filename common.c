#include "common.h"


int lenToNextDelim(char* str, char delim)
{
    int len = 0;
    while(str[len] != 0 && str[len] != delim)
    {
        len++;
    }

    return len;
}

int nDelimInd(char* str, int n, char delim)
{
    int ind = 0;

    if (n == 0)
    {
        return -1;
    }


    while (str[ind] != 0 && n > 0)
    {
        ind++;
        if (str[ind] == delim || str[ind] == 0)
        {
            n--;
        }        
    }
    
    if (n) /*if nth delimeter doesn't exist*/
    {
        return -1;
    }
    else
    {
        return ind;
    }
    
}

int cpyncol(char* dest, char* src, int col, int lim, char delim)
{
    int colStart = 0;

    colStart = nDelimInd(src, col - 1, delim);

    if (col >= 0)
    {
        strncpy(dest, src + colStart + 1, lim - 1);
        dest[lim - 1] = 0;
        return 1;
    }
    else
    {
        return 0;
    }
}

char* cpycol (char* dest, char* src, int* arrLen, int col, char delim)
{
    int colStart;
    int colLen;
    int delimOffset = 1;

    colStart = nDelimInd(src, col - 1, delim);

    if (colStart == -1)
    {
        colStart++;
        delimOffset = 0;
    }

    if (src[colStart] != 0)
    {
        colLen = nDelimInd(src + colStart + delimOffset, 1, delim);
    }
    else
    {
        colLen = 0;
    }
    
    if (colLen > 0)
    {
        if (dest == NULL || *arrLen < colLen + 1)
        {
            dest = realloc(dest, sizeof(char) * (colLen + 1));
            *arrLen = colLen + 1;
        }

        strncpy(dest, src + colStart + delimOffset, colLen);
        dest[colLen] = 0;
        return dest;
    }

    free(dest);
    *arrLen = 0;
    return NULL;

    
}

void appendRef(struct refList* l, void* newElement)
{
    if (l->arrLen == l->arrSpace)
    {
        l->arrSpace = l->arrSpace * 2 + 1;
        l->arr = realloc(l->arr, sizeof(void*) * l->arrSpace);
    }

    (l->arr[l->arrLen]) = newElement;
    l->arrLen++;


    return;
}


void** createPtrArr(void* base, size_t nmemb, size_t size)
{
    void** newPtrArr;

    newPtrArr = malloc(sizeof(void*) * nmemb);

    if (newPtrArr)
    {
        int x;
        for (x = 0; x < nmemb; x++)
        {
            newPtrArr[x] = base;
            /*the compiler doesn't like me performing pointer arithmetic 
              on a void pointer so here we are*/
            base = (void*)((uint8_t*)base + size);
        }
    }

    return newPtrArr;
}

void* passThrough(void* p)
{
    return p;
}

char* promptGetInput(char* prompt)
{
    char* input = NULL;
    char next;
    int space = 2;
    int length = 0;
    printf("%s", prompt);

    input = malloc(space);

    do
    {
        next = fgetc(stdin);
        if (length + 1 > space)
        {
            input = realloc(input, (space *= 2));
        }
        input[length] = next;
        length++;
        
    } while (next != '\n');

    input[length - 1] = 0;
    return input;
}



char* chomp(char* str)
{
    char* chomped;
    int length = strlen(str);
    int spacesBefore = 0;
    int spacesAfter = 0;
    int x;

    for (x = 0; x < length; x++)
    {
        if (str[x] == ' ')
        {
            spacesBefore++;
        }
        else
        {
            break;
        }
    }

    for (x = length - 1; x >= 0; x--)
    {
        if (str[x] == ' ')
        {
            spacesAfter++;
        }
        else
        {
            break;
        }
    }

    if (!((length - spacesBefore == 0) || (length - spacesAfter == 0)))
    {
        chomped = malloc(length - spacesAfter - spacesBefore + 1);

        chomped = strncpy(chomped, str + spacesBefore, length - spacesAfter - spacesBefore);
        chomped[length - spacesAfter - spacesBefore] = 0;
        free(str);

        return chomped;
    }

    return str;

}


char* getFirstWord(char* str)
{
    int x;
    int y;
    int len = strlen(str);
    char* firstWord = NULL;
    for (x = 0; x < len; x++)
    {
        if (str[x] != ' ') break;
    }

    if (x != len - 1)
    {
        for (y = x; y < len; y++)
        {
            if (str[y] == ' ') break;
        }

        firstWord = (char*)malloc(sizeof (char)  * (y - x + 1));
        strncpy(firstWord, str + x, y - x);
        firstWord[y - x] = 0;
        
    }


    return firstWord;

}

void changeFirstWordToSpace(char* str)
{
    int len = strlen(str);
    int x;
    int y;
    for (x = 0; x < len; x++)
    {
        if (str[x] != ' ') break;
    }

    for (y = x; y < len; y++)
    {
        if (str[y] == ' ')
        {
            return;
        }
        else
        {
            str[y] = ' ';
        }
        
    }
    return;
}