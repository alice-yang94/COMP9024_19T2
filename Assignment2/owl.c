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
#include "Quack.h"

#define MAX_WORD_LEN 20
#define MAX_NODE 1000

// used for differByOne functions
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
 * (words are nodes, differByOne relationship is an edge)
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
 * Input: a graph with words differ by one,
 *        an int with array length,
 *        a pointer to an int to store the longest ladder length,
 *        a queue to store all start nodes of longest paths
 * Returns: an array of stacks, each stores the longest paths' 
 *          next node from the current node 
 * 
 * Get the longest ladders from given graph
*/
Quack* getLongestLadders(Graph, int, int *, Quack);

/**
 * Input: a current node, 
 *        a differByOne graph, 
 *        total number of words,
 *        a int array to store the current max length from each node,
 *        an array of stacks, each to store the longest paths' 
 *          next node from the current node
 * Returns: the longest path length from currNode
 * 
 * Get the longest ladders from given node
*/
int dfsR(Vertex, Graph, int, int *, Quack *);

/**
 * Input: an array of stacks with the longest paths' next node 
 *             from the current node,
 *        a queue with all start nodes of longest paths,
 *        an array of input words
 * Returns: void
 * 
 * Print longest ladders
*/
void printLongestLadders(Quack *, Quack, char **);

/**
 * Input: a queue storing one of the longest path,
 *        the next popping node's last node,
 *        the count index of path
 *        an array of input words
 * Returns: void
 * 
 * Print the words in the order stored in path, and push them back
*/
void printPath(Quack, int, int *, char **);

/**
 * Input: an array of stacks, a int with number of words
 * Returns: a NULL pointer
 * 
 * Free all spaces allocated for the array of stacks
*/
Quack* freeQuackArray(Quack*, int);


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

            // calculate longest ladders with generated graph
            int longestLen = 0;
            Quack maxLenStartNodes = createQuack();
            Quack* pathStacks = getLongestLadders(g, numWords,
                &longestLen, maxLenStartNodes);

            if (pathStacks == NULL) {
                exitStatus = EXIT_FAILURE;
            } else {
                // print the longest ladders...
                printf("Longest ladder length: %d\n", longestLen);

                /**debugging info
                printf("\nFinal\n");
                for (int i=0; i<numWords; i++) {
                    printf("path stack %d: ", i);
                    showQuack(pathStacks[i]);
                }
                debugging info*/

                printLongestLadders(pathStacks, maxLenStartNodes, 
                    wordArray);

                // free the memory allocated
                pathStacks = freeQuackArray(pathStacks, numWords);
                pathStacks = NULL;
            }
            
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

// Check if two strings are differ by one letter
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

// Check if one str changes one letter can become another 
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

// Check if str1 can transform to str2 by adding one letter
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

// Allocate memory for the word array
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

// Free the space allocate for word array
char ** freeWordArray(char ** wordArray) {
    int i;
    for (i=0; i<MAX_NODE; i++) {
        free(wordArray[i]);
    }
    free(wordArray);
    return NULL;
}

// Read the words in stdin and generate a differByOne graph 
Graph readInput(char ** wordArray, int * numWords) {
    // Read input from stdin to wordArray
    while (scanf("%s", wordArray[*numWords]) != EOF) {
        if (*numWords == 0) {
            (*numWords)++;
        } else if (strcmp(wordArray[*numWords],
                        wordArray[(*numWords) - 1]) != 0) {
            (*numWords)++;
        }    
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

// Print out the words and their index as a dictionary
void printDictionary(char ** wordArray, int numWords) {
    int i;
    printf("Dictionary\n");
    for (i=0; i<numWords; i++) {
        printf("%d: %s\n", i, wordArray[i]);
    }
    return;
}

// Search for the longest ladders from the differByOne graph
Quack* getLongestLadders(Graph g, int numWords, int * longestLen, 
                         Quack maxLenStartNodes) 
{
    // an array of stacks, each stack stored next node of the longest 
    //    paths start from the node(index of word) 
    Quack * pathStacks = malloc(numWords * sizeof(Quack));

    // visitedArray[i] stores the max ladder length starting from node i
    int * visitedArray = malloc(numWords * sizeof(int));
    
    if (visitedArray == NULL || pathStacks == NULL) {
        fprintf(stderr, "getLongestLadders: out of memory\n");
    } else {
        int i;
        for (i=0; i<numWords; i++) {
            // initialise unvisited node with max length -1
            visitedArray[i] = -1;
            // initialise all path stacks as empty stacks
            pathStacks[i] = createQuack();
        }
        // DFS on each unvisited node until all nodes visited
        qush(0, maxLenStartNodes);
        *longestLen = dfsR(0, g, numWords, visitedArray, pathStacks);
        
        if (numWords > 1) {
            int startNode;
            for (startNode = 1; startNode < numWords; startNode++) {
                if (visitedArray[startNode] == -1) {
                    int newLen = dfsR(startNode, g, numWords, visitedArray, 
                        pathStacks);

                    if (newLen > *longestLen) {
                        *longestLen = newLen;
                        makeEmptyQuack(maxLenStartNodes);
                        qush(startNode, maxLenStartNodes);
                    } else if (newLen == *longestLen) {
                        qush(startNode, maxLenStartNodes);
                    }
                }
            }
        }

        // destroy visitedArray
        free(visitedArray);
        visitedArray = NULL;
    
    }
    return pathStacks;
}

// Search and record the longest ladders from given node using recursion
int dfsR(Vertex currNode, Graph g, int numWords, int * visitedArray, 
        Quack * pathStacks) 
{
    int maxLen = 1;
    if (visitedArray[currNode] != -1) { // currNode is visited
        maxLen = visitedArray[currNode];
    
    } else { // currNode is unvisited
        
        /**debugging info
        printf("unvisited: %d\n", currNode);
        printf("visited array: ");
        for (int i=0; i<numWords; i++) {
            printf("%d ", visitedArray[i]);
        }
        printf("\n");
        for (int i=0; i<numWords; i++) {
            printf("path stack %d: ", i);
            showQuack(pathStacks[i]);
        }
        debugging info*/


        bool hasUnvisitedChild = false;
        int child;
        for (child = currNode+1; child < numWords; child++) {
            if (isEdge(newEdge(currNode,child), g)) {
                
                /**debugging info
                printf("child: %d\n", child);
                printf("visited array: ");
                for (int i=0; i<numWords; i++) {
                    printf("%d ", visitedArray[i]);
                }
                printf("\n");
                for (int i=0; i<numWords; i++) {
                    printf("path stack %d: ", i);
                    showQuack(pathStacks[i]);
                }
                debugging info*/



                // if the child is not visited, calculate the longest 
                //  path from it, else, using the recorded length
                int currMaxLen = 1 + visitedArray[child];
                if (visitedArray[child] == -1) {
                    hasUnvisitedChild = true;
                    currMaxLen = 1 + dfsR(child, g, numWords, 
                        visitedArray, pathStacks);
                } 

                /**debugging info
                printf("visited array: ");
                for (int i=0; i<numWords; i++) {
                    printf("%d ", visitedArray[i]);
                }
                printf("\n");
                for (int i=0; i<numWords; i++) {
                    printf("path stack %d: ", i);
                    showQuack(pathStacks[i]);
                }
                printf("currMaxLen: %d\n", currMaxLen);
                printf("maxLen: %d\n", maxLen);
                debugging info*/



                // if new length bigger, empty the quack and  the 
                //  current child; if equals, push the child to the quack
                if (currMaxLen > maxLen) {
                    maxLen = currMaxLen;
                    makeEmptyQuack(pathStacks[currNode]);
                    push(child, pathStacks[currNode]);
                } else if (currMaxLen == maxLen) {
                    push(child, pathStacks[currNode]);
                }

            }
        }

        visitedArray[currNode] = maxLen;
    }

    return maxLen;
}

// print longest ladders using path Stacks and start nodes
void printLongestLadders(Quack * pathStacks, Quack maxLenStartNodes,
    char ** wordArray) 
{
    printf("Longest ladders:\n");
    int order = 1;
    while (!isEmptyQuack(maxLenStartNodes) && order < 100) {
        int startNode = pop(maxLenStartNodes);
        Quack startStack = pathStacks[startNode];
        if (isEmptyQuack(startStack)) {
            printf("%2d: %s\n", order, wordArray[startNode]);
            order++;
        } else {
            // Using dfs to print the paths by keeping record of 
            //current path, current node and last node of current node
            Quack currStack = createQuack();
            Quack lastStack = createQuack();
            Quack fullPath = createQuack();
            
            push(startNode, currStack);
            push(-1, lastStack);

            while (!isEmptyQuack(currStack) && order < 100) {
                int currNode = pop(currStack);
                int lastNode = pop(lastStack);
                qush(currNode, fullPath);
                // childStack contains all children of currNode
                Quack childStack = pathStacks[currNode];

                /**debug
                printf("path: ");
                showQuack(fullPath);
                printf("currQ: ");
                showQuack(childStack);
                printf("currStack: ");
                showQuack(currStack);*/
                

                // if childStack is empty, path end reached, print path
                if (isEmptyQuack(childStack)) {
                    int nextLast = -1;
                    if (!isEmptyQuack(lastStack)) {
                        nextLast = pop(lastStack);
                        push(nextLast, lastStack);
                    }

                    //printf("nextLast: %d\n", nextLast);
                    
                    
                    printPath(fullPath, nextLast, &order, wordArray);

                } else {
                    // if childStack is not empty, push all children to stack
                    int firstChild = pop(childStack);
                    int child = firstChild;
                    bool equalsFirstChild = false;
                    if (isEmptyQuack(childStack)) {
                        qush(child, childStack);
                        push(child, currStack);
                        push(currNode, lastStack);
                    } else {
                        while (!isEmptyQuack(childStack) 
                            && !equalsFirstChild) {
                            // has to qush back to the childStack in case other
                            //start node has path via this node
                            qush(child, childStack);
                            push(child, currStack);
                            push(currNode, lastStack);

                            child = pop(childStack);
                            if (child == firstChild) {
                                equalsFirstChild = true;
                                push(child, childStack);
                            }
                        }
                    }

                        /**debug
                    printf("path: ");
                    showQuack(fullPath);
                    printf("currQ: ");
                    showQuack(childStack);
                    printf("currStack: ");
                    showQuack(currStack);*/
                }
            
            }
            makeEmptyQuack(currStack);
            makeEmptyQuack(lastStack);
            makeEmptyQuack(fullPath);
        }
        
    }
    return;
}

// Print the words in the order stored in path, and push them back
void printPath(Quack fullPath, int nextLast, int *order, char **wordArray)
{
    /**Debug
    showQuack(fullPath);*/
    

    Quack stack = createQuack();
    bool foundLast = false;
    // nextLast = -1 indicates the current queue is empty, do not need 
    //to retain path to the previous situation
    
    int curr = pop(fullPath);
    if (!foundLast) {
        push(curr, stack);
    }
    if (curr == nextLast || nextLast == -1) {
        foundLast = true;
    }
    
    printf("%2d: %s", *order, wordArray[curr]);

    while (!isEmptyQuack(fullPath)) {
        curr = pop(fullPath);
        printf(" -> %s", wordArray[curr]);
        if (!foundLast) {
            push(curr, stack);
        }
        if (curr == nextLast) {
            foundLast = true;
        }
    }
    putchar('\n');
    (*order)++;

    while (!isEmptyQuack(stack)) {
        push(pop(stack), fullPath);
    }

    /** debug 
    printf("path: ");
    showQuack(fullPath);
    printf("\n");*/

    return;
}

// Free all spaces allocated for the array of quacks
Quack* freeQuackArray(Quack* pathStacks, int numWords) {
    int i;
    for (i=0; i<numWords; i++) {
        pathStacks[i] = destroyQuack(pathStacks[i]);
    }
    free(pathStacks);
    return pathStacks;
}