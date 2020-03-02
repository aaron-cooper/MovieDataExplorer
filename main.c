#include <stdio.h>
#include "common.h"
#include "name.h"
#include "title.h"
#include "principals.h"
#include "binary.h"
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    struct name_basics* nbarr;
    int nbarrlen;
    struct title_basics* tbarr;
    int tbarrlen;
    struct title_principals* tparr;
    int tparrlen;
    char* input = NULL;
    char* firstWord = NULL;
    char* searchTerm = NULL;

    struct tree_node* nbnconstTree;
    struct tree_node* nbpnamTree;
    struct tree_node* tbtconstTree;
    struct tree_node* tbptitleTree;
    struct tree_node* tptconstTree;
    struct tree_node* tpnconstTree;

    char* nbfilename;
    char* tbfilename;
    char* prinfilename;

    void** ptrarr;


    nbfilename = malloc (strlen(argv[1]) + 256);
    tbfilename = malloc (strlen(argv[1]) + 256);
    prinfilename = malloc (strlen(argv[1]) + 256);

    nbfilename = strcpy(nbfilename, argv[1]);
    tbfilename = strcpy(tbfilename, argv[1]);
    prinfilename = strcpy(prinfilename, argv[1]);

    nbfilename = strcat(nbfilename, "/name.basics.tsv");
    tbfilename = strcat(tbfilename, "/title.basics.tsv");
    prinfilename = strcat(prinfilename, "/title.principals.tsv");

    nbarr = constructNameBasicsArr(nbfilename, &nbarrlen);
    tbarr = constructTitleBasicsArr(tbfilename, &tbarrlen);
    tparr = constructTitlePrincipalsArr(prinfilename, &tparrlen);

    free(nbfilename);
    free(tbfilename);
    free(prinfilename);

    ptrarr = createPtrArr(nbarr, nbarrlen, sizeof(struct name_basics));

    

    nbnconstTree = constructTreeFromSortedArray(ptrarr, nbarrlen, sizeof(void*), NBDeref);
    qsort(ptrarr, nbarrlen, sizeof(void*), compareNBPptr);
    nbpnamTree = constructTreeFromSortedArray(ptrarr, nbarrlen, sizeof(void*), NBDeref);

    free(ptrarr);

    ptrarr = createPtrArr(tbarr, tbarrlen, sizeof(struct title_basics));

    tbtconstTree = constructTreeFromSortedArray(ptrarr, tbarrlen, sizeof(void*), TBDeref);
    qsort(ptrarr, tbarrlen, sizeof(void*), compareTPTptr);
    tbptitleTree = constructTreeFromSortedArray(ptrarr, tbarrlen, sizeof(void*), TBDeref);

    free(ptrarr);

    ptrarr = createPtrArr(tparr, tparrlen, sizeof(struct title_principals));

    tptconstTree = constructTreeFromSortedArray(ptrarr, tparrlen, sizeof(void*), TPDeref);

    qsort(ptrarr, tparrlen, sizeof(void*), comparePNCptr);
    tpnconstTree = constructTreeFromSortedArray(ptrarr, tparrlen, sizeof(void*), TPDeref);



    while(1)
    {
        input = promptGetInput("> ");
        firstWord = getFirstWord(input);
        changeFirstWordToSpace(input);
        searchTerm = chomp(input);
        input = NULL;

        if (!strcmp(firstWord, "name"))
        {

            struct refList actorResults = {0,0,0};
            struct refList tconstResults = {0,0,0};
            struct name_basics inputNB;
            int x;

            inputNB.primaryName = searchTerm;

            /*search for nconst*/
            actorResults = searchTree(nbpnamTree, &inputNB, actorResults, compareNamePrimaryName);

            /*search for tconst*/
            for( x = 0; x < actorResults.arrLen; x++)
            {
                struct title_principals curr;
                curr.nconst = ((struct name_basics*)(actorResults.arr[x]))->nconst;
                tconstResults = searchTree(tpnconstTree, &curr, tconstResults, comparePrincipalsNConst);
            }

            free(actorResults.arr);

            for (x = 0; x < tconstResults.arrLen; x++)
            {
                struct title_principals curr;
                struct title_basics tb;
                struct refList r = {0,0,0};
                curr = *((struct title_principals *)(tconstResults.arr[x]));
                tb.tconst = curr.tconst;
                r = searchTree(tbtconstTree, &tb, r, compareTitleTConst);
                if (r.arr != NULL)
                {

                    tb = *((struct title_basics*)(r.arr[0]));

                    printf("%s : %s", tb.primaryTitle, curr.characters);
                }

                free(r.arr);
            }

            free(tconstResults.arr);



        }
        else if (!strcmp(firstWord, "title"))
        {
            struct title_basics inputTB;
            struct refList tconstValues = {0,0,0};
            struct refList nconstValues = {0,0,0};
            int x;



            inputTB.primaryTitle = searchTerm;

            tconstValues = searchTree(tbptitleTree, &inputTB, tconstValues, compareTitlePrimaryTitle);

            for (x = 0; x < tconstValues.arrLen; x++)
            {
                struct title_principals curr;
                curr.tconst = ((struct title_basics*)(tconstValues.arr[x]))->tconst;
                nconstValues = searchTree(tptconstTree, &curr, nconstValues, comparePrincipalsTConst);
            }
            free(tconstValues.arr);

            for (x = 0;x < nconstValues.arrLen; x++)
            {
                struct title_principals curr;
                struct name_basics nb;
                struct refList r = {0,0,0};
                curr = *((struct title_principals *)(nconstValues.arr[x]));
                nb.nconst = curr.nconst;
                r = searchTree(nbnconstTree, &nb, r, compareNameNConst);

                if (r.arr != NULL)
                {
                    nb = *((struct name_basics*)(r.arr[0]));
                    printf("%s : %s", nb.primaryName, curr.characters);
                }
                free(r.arr);
            }
            free(nconstValues.arr);

        }
        

        free(firstWord);
        free(searchTerm);


    }
    free(ptrarr);

    freeTree(nbnconstTree);
    freeTree(nbpnamTree);
    freeTree(tbtconstTree);
    freeTree(tbptitleTree);
    freeTree(tptconstTree);
    freeTree(tpnconstTree);

    freeNameBasics(nbarr, nbarrlen);
    freeTitleBasics(tbarr, tbarrlen);
    freeTitlePrincipalsArr(tparr, tparrlen);

    return 0;
}





