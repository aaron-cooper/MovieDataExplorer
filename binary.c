#include "binary.h"


/*
struct tree_node* constructNameBasicsTree(struct name_basics* arr, int arrLen)
{
    struct tree_node* newTree;
    
    newTree = malloc (sizeof(struct tree_node));
    newTree->left = NULL;
    newTree->right = NULL;
    
    if (arrLen == 1)
    {
        newTree->data = arr;
    }
    else if (arrLen == 2)
    {
        newTree->data = arr + 1;
        newTree->left = constructNameBasicsTree(arr, 1);
    }
    else
    {
        int middle = arrLen / 2;
        newTree->data = arr + middle;
        newTree->left = constructNameBasicsTree(arr,middle);
        newTree->right = constructNameBasicsTree(arr + middle + 1, arrLen - middle - 1);
    }
    
    return newTree;    
}
*/



struct tree_node* constructTreeFromSortedArray(void* arr, int arrLen, size_t size, void* (*dereferencer)(void*))
{
    struct tree_node* newTree;
    
    newTree = malloc (sizeof(struct tree_node));
    newTree->left = NULL;
    newTree->right = NULL;
    
    if (arrLen == 1)
    {
        newTree->data = (*dereferencer)(arr);
    }
    else if (arrLen == 2)
    {
        /*perror*/
        newTree->data = (*dereferencer)((uint8_t*)arr + size);
        newTree->left = constructTreeFromSortedArray(arr, 1, size, dereferencer);
    }
    else
    {
        int middle = arrLen / 2;
        newTree->data = (*dereferencer)((uint8_t*)arr + (middle * size));
        newTree->left = constructTreeFromSortedArray(arr, middle, size, dereferencer);
        newTree->right = constructTreeFromSortedArray((uint8_t*)arr + ((middle + 1) * size), arrLen - middle - 1, size, dereferencer);
    }
    
    return newTree;    
}

struct tree_node* constructTreeFromArray(void* arr, int arrLen, size_t size, int (*compar)(const void*, const void*))
{
    struct tree_node* tree = NULL;
    int x;
    uint8_t* arr_;
    arr_ = arr;
    /*perror*/
    for (x = 0; x < arrLen; x++)
    {
        tree = insertTreeNode(tree, arr_, compar);
        arr_ += size;
    }

    return tree;
}

struct tree_node* insertTreeNode(struct tree_node* tree, void* toInsert, int (*compar)(const void*, const void*))
{

    if (tree == NULL)
    {
        tree = malloc(sizeof(struct tree_node));
        tree->data = toInsert;
        tree->left = NULL;
        tree->right = NULL;
        return tree;
    }
    else
    {
        int inserted = 0;
        struct tree_node* root = tree;
        while (!inserted)
        {
            if ((*compar)(toInsert, tree->data) < 1)
            {
                if (tree->left == NULL)
                {
                    tree->left = malloc(sizeof(struct tree_node));
                    tree->left->data = toInsert;
                    tree->left->right = NULL;
                    tree->left->left = NULL;
                    inserted = 1;
                }
                else
                {
                    tree = tree->left;
                }            
            }
            else
            {
                if (tree->right == NULL)
                {
                    tree->right = malloc(sizeof(struct tree_node));
                    tree->right->data = toInsert;
                    tree->right->right = NULL;
                    tree->right->left = NULL;
                    inserted = 1;
                }
                else
                {
                    tree = tree->right;
                }            
            }        
        }
        return root;
    }
}

void freeTree(struct tree_node* tree)
{
    if (tree->left != NULL)
    {
        freeTree(tree->left);
    }

    if (tree->right != NULL)
    {
        freeTree(tree->right);
    }

    free(tree);
    return;
}



void printTree(struct tree_node* tree, void (*print)(const void*))
{
    if (tree != NULL)
    {
        printTree(tree->left, print);
        (*print)(tree->data);
        printTree(tree->right, print);
    }
    return;
}

struct refList searchTree(struct tree_node* tree, const void* target, struct refList result, int (*compar)(const void*, const void*))
{
    int cmpRes;

    cmpRes = compar(target, tree->data);

    if (cmpRes == 0)
    {
        appendRef(&result, tree->data);
        if (tree->left != NULL)
        {
            result = searchTree(tree->left, target, result, compar);
        }

        if (tree->right != NULL)
        {
            result = searchTree(tree->right, target, result, compar);
        }
        return result;
    }
    else if (cmpRes > 0)
    {
        if (tree->right != NULL)
        {
            result = searchTree(tree->right, target, result, compar);
        }
        return result;
    }
    else
    {
        if (tree->left != NULL)
        {
            result = searchTree(tree->left, target, result, compar);
        }
        return result;
    }
    
}
