#ifndef BINARY_H
#define BINARY_H

#include <stdlib.h>
#include "name.h"
#include <stdint.h>

struct tree_node {
    void* data;
    struct tree_node* left;
    struct tree_node* right;
};


/*struct tree_node* constructNameBasicsTree(struct name_basics* arr, int arrLen);*/

struct tree_node* constructTreeFromSortedArray(void* arr, int arrLen, size_t size, void* (*dereferencer)(void*));

struct tree_node* constructTreeFromArray(void* arr, int arrLen, size_t size, int (*compar)(const void*, const void*));

struct tree_node* insertTreeNode(struct tree_node* tree, void* toInsert, int (*compar)(const void*, const void*));

void freeTree(struct tree_node* tree);

void printTree(struct tree_node* tree, void (*print)(const void*));

struct refList searchTree(struct tree_node* tree, const void* target, struct refList result, int (*compar)(const void*, const void*));

#endif