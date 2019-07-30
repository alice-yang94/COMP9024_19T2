/**
 * COMP9024 Assignment 2: Ordered Word Ladders 
 * 
 * @author Wenke Yang
 * @email z5230655@student.unsw.edu.au
 * @create date 2019-07-15 22:18:34
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "Graph.h"
#include "differByOne.h"
#include "Quack.h"

#define MAX_WORD_LEN 20
#define MAX_NODE 1000
#define FIRST_STR_SHORTER_CODE 2
#define SECOND_STR_SHORTER_CODE 3

/**
 * Input: two null-terminated strings
 * Returns: bool
 * 
 * Check if the two strings satisfy one of the 2 conditions below:
 * 1. changing one letter, e.g. barn→born
 * 2. adding or removing one letter, e.g. band→brand and bran→ran
 * 
*/
bool differByOne(char *, char *);

/**
 * Input: two null-terminated strings with same length
 * Returns: bool
 * 
 * Check if one str changes one letter can become another 
*/
bool changeOne(char *, char *);

/**
 * Input: two null-terminated strings, str1 and str2
 *        str1 is shorter than str2 by 1.
 * Returns: bool 
 * 
 * Check if str1 can transform to str2 by adding one letter
*/
bool addOrRemoveOne(char *, char *);

/**
 * Input: void
 * Returns: an empty array of words
 * 
 * Create an array with space for max. 1000 words, 
 * each word with max. 20 characters
 */
char ** initialiseWordArray(void);

/**
 * free all memory spaces alloced for the word array
*/
char ** freeWordArray(char **);

/**
 * Input: an empty array of string, a pointer to an int
 * Returns: a graph
 * 
 * Read words from stdin,  
 * generate a differByOne graph using these words,
 * store the words in the given array, the length in the int 
*/
Graph readInput(char **, int *);

/**
 * Input: an array of words, an int with array length
 * Returns: void
 * 
 * Print index and corresponding words int the given array 
*/
void printDictionary(char **, int);

/**
 * Input: a graph with words differ by one, a pointer to an int,
 *        an int with array length
 * Returns: a linked list of arrays
 * 
 * Get the longest ladders from given graph in the following form:
 * [ladder1 word ids] --> [ladder2 word ids] ... 
 *            [0,1,3] --> [0,2,4] ...
 * and store the longest ladder length in the given int.
*/
Quack getLongestLadders(Graph, int *, int);

int dfsStack(Graph, Vertex, int, int *);

int main(void) {
    // malloc enough space to store the input words
    char ** wordArray = initialiseWordArray();
    int exitStatus = EXIT_SUCCESS;

    if (wordArray == NULL) {
        exitStatus = EXIT_FAILURE;
    } else {
        // read input from stdin and generate differByOne graph
        int numWords = 0;
        Graph g = readInput(wordArray, &numWords);
        if (g == NULL) {
            exitStatus = EXIT_FAILURE;
        } else {
            // print out dictionary and graph
            printDictionary(wordArray, numWords);
            printf("Ordered Word Ladder Graph\n");
            showGraph(g);

            /* 
            // calculate longest ladders with generated graph
            int longestLen = 0;
            Quack longestLadders = getLongestLadders(g, &longestLen, 
                                                    numWords);
            if (longestLadders == NULL) {
                exitStatus = EXIT_FAILURE;
            } else {
                // print the longest ladders...

                // free the memory allocated
                longestLadders = destroyQuack(longestLadders);
                longestLadders = NULL;
            }
            */
            // free the memory allocated
            g = freeGraph(g);
            g = NULL;
        }
        // free the memory allocated
        wordArray = freeWordArray(wordArray);
        wordArray = NULL;
    }
    return exitStatus;
}

bool differByOne(char * str1, char * str2) {
    bool isdifferbyOne = false;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int lenDiff = len1 - len2;

    switch (lenDiff) {
        case 0:
            // same length
            isdifferbyOne = changeOne(str1, str2);
            break;
        case 1:
            // diff in length == 1, str2 is shorter
            isdifferbyOne = addOrRemoveOne(str2, str1);
            break;
        case -1:
            // diff in length == 1, str1 is shorter
            isdifferbyOne = addOrRemoveOne(str1, str2);
            break;
        default:
            // diff in length > 1
            break;
    }

    return isdifferbyOne;
}

bool changeOne(char * str1, char * str2) {
    int i = 0;
    char c1 = *str1;
    char c2 = *str2;
    int diff = 0;

    while (c1 != '\0' && diff <= 1) {
        if (c1 != c2) {
            diff++;
        }

        i++;
        c1 = *(str1+i);
        c2 = *(str2+i);
    }

    bool changeOneResult = false;
    if (diff == 1) {
        changeOneResult = true;
    }
    return changeOneResult;
}

bool addOrRemoveOne(char * str1, char * str2) {
    int i1 = 0;
    int i2 = 0;
    char c1 = *str1;
    char c2 = *str2;
    int diff = 0;

    while (c1 != '\0' && diff <= 1) {
        if (c1 == c2) {
            i1++;
        } else {
            diff++;
        }
        i2++;
        c1 = *(str1+i1);
        c2 = *(str2+i2);
    }

    bool addOne = false;
    if (diff <= 1) {
        addOne = true;
    }
    return addOne;
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

char ** freeWordArray(char ** wordArray) {
    int i;
    for (i=0; i<MAX_NODE; i++) {
        free(wordArray[i]);
    }
    free(wordArray);
    return NULL;
}

Graph readInput(char ** wordArray, int * numWords) {
    // Read input from stdin to wordArray
    while (scanf("%s", wordArray[*numWords]) != EOF) {
        (*numWords)++;
    }

    Graph g = NULL;
    if (*numWords > 0) {
        g = newGraph(*numWords);
        if (g != NULL) {
            // For each pair of words, if they are differ by one letter,
            //    they are connected by an edge in the graph.
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

Quack getLongestLadders(Graph g, int * longestLen, int numWords) {
    Quack longestLadders = NULL;
    
    // maxLenStartWith[i] stores the max ladder length starting from node i
    int * maxLenStartWith = malloc(numWords * sizeof(int));
    if (maxLenStartWith == NULL) {
        fprintf(stderr, "getLongestLadders: out of memory\n");
    } else {
        int i;
        for (i=0; i<numWords; i++) {
            maxLenStartWith[i] = -1;
        }
        longestLadders = createQuack();
        // DFS on each unvisited node until all nodes visited
        while (i < numWords) {
            if (maxLenStartWith[i] == -1) {
                int newLen = dfsStack(g, i, numWords, maxLenStartWith);
                if (newLen > *longestLen) {

                } else if (newLen == *longestLen) {

                }
            }
            i++;
        }

        
    
    }
    return longestLadders;
}

int dfsStack(Graph g, Vertex rootv, int numV, int * maxLenStartWith) {
    int maxLen = 0;
    Quack stack = createQuack();
    push(0, stack);
    //...

    stack = destroyQuack(stack);
    return maxLen;
}