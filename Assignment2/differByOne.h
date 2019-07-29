#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
