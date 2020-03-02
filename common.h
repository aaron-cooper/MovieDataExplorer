#ifndef COMMON_H
#define COMMON_H
#define MAX_LINE_LEN 1000

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

struct refList
{
    void** arr;
    unsigned int arrLen;
    unsigned int arrSpace;
};

/*
 * lenToNextDelim: counts the number of characters in a string before the next 
 *  delim or null character
 * Param:
 *  char* str: pointer to the beginning of the string to check
 *  char delim: the delimiter
 * return: the number of characters in the string before the first delim or null
 *  character
 */
int lenToNextDelim(char* str, char delim);

int nDelimInd(char* str, int n, char delim);

int cpyncol(char* dest, char* src, int col, int lim, char delim);


char* cpycol (char* dest, char* src, int* arrLen, int col, char delim);

void appendRef(struct refList* l, void* newElement);

void** createPtrArr(void* base, size_t nmemb, size_t size);

void* passThrough(void* p);

char* promptGetInput(char* prompt);

char* chomp(char* str);

char* getFirstWord();

void changeFirstWordToSpace(char* str);

#endif