#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Graph.h"
#include "differByOne.h"

#define MAX_WORD_LEN 20
#define MAX_NODE 1000

/**
 * Input: void
 * Returns: an empty array of words
 * 
 * Creates an array with 1000 words, each word with 20 characters
 */
char ** initialiseWordArray(void);

/**
 * Input: an array of words, a pointer to int
 * Returns: a graph
 * 
 * Generate a differByOne graph using the given array of words
*/
Graph readInput(char **, int *);

/**
 * Input: an array of words, an int
 * Returns: void
 * 
 * print index and corresponding words int the given array 
*/
void printDictionary(char **, int);

int main(void) {
    int numWords = 0;
    char ** wordArray = initialiseWordArray();
    int exitStatus = EXIT_SUCCESS;

    if (wordArray == NULL) {
        exitStatus = EXIT_FAILURE;
    } else {
        Graph g = readInput(wordArray, &numWords);
        if (g == NULL) {
            exitStatus = EXIT_FAILURE;
        } else {
            printDictionary(wordArray, numWords);
            printf("Ordered Word Ladder Graph\n");
            showGraph(g);
        }
    }
    return exitStatus;
}

char ** initialiseWordArray(void) {
    char ** wordArray = NULL;
    wordArray = malloc(MAX_NODE * sizeof(char *));
    if (wordArray == NULL) {
        fprintf(stderr, "initialise WordArray: out of memory\n");
    } else {
        int i;
        int success = 1;
        for (i=0; i<MAX_NODE && success; i++) {
            wordArray[i] = malloc(MAX_WORD_LEN * sizeof(char));
            if (wordArray[i] == NULL) {
                fprintf(stderr, "initialise WordArray: out of memory\n");
                success = 0;
            }
        }
    }
    return wordArray;
}

Graph readInput(char ** wordArray, int * numWords) {
    Graph g = NULL;

    while (scanf("%s", wordArray[*numWords]) != EOF) {
        (*numWords)++;
    }
    
    if (*numWords > 0) {
        g = newGraph(*numWords);
        if (g != NULL) {
            int i,j;
            for (i=0; i<*numWords; i++) {
                for (j=i+1; j<*numWords; j++) {
                    if (differByOne(wordArray[i], wordArray[j])) {
                        insertEdge(newEdge(i,j), g);
                    }
                }
            }
        }
    }
       
    return g;
}

void printDictionary(char ** wordArray, int numWords) {
    int i;
    printf("Dictionary\n");
    for (i=0; i<numWords; i++) {
        printf("%d: %s\n", i, wordArray[i]);
    }
}