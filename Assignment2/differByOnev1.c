/**
 * COMP9024 Assignment 2: Ordered Word Ladders version 1
 * 
 * @author Wenke Yang
 * @email z5230655@student.unsw.edu.au
 * @create date 2019-07-15 22:18:34
 * @description 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FIRST_STR_SHORTER_CODE 2
#define SECOND_STR_SHORTER_CODE 3

#define INPUT_STR_SIZE 100
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
 * Input: two null-terminated strings
 * Returns: int - 0: false
 *                1: true
 *                2: first str is shorter [FIRST_STR_SHORTER_CODE]
 *                3: second str is shorter [SECOND_STR_SHORTER_CODE]
 * 
 * Check if one string can transform to another by 
 * changing one letter
*/
int changeOneLetter(char *, char *);

/**
 * Input: two null-terminated strings, str1 and str2
 *        str1 is shorter than str2 by 1, and 1 letter difference.
 * Returns: bool 
 * 
 * Check if str1 can transform to str2 by adding one letter
*/
bool addOrRemoveOne(char *, char *);

int main(void) {
    char str1[INPUT_STR_SIZE];
    char str2[INPUT_STR_SIZE];
    printf("Enter the first string:\n");
    scanf("%s", str1);
    printf("%s\n", str1);

    printf("Enter the second string:\n");
    scanf("%s", str2);
    printf("%s\n", str2);

    if (differByOne(str1, str2)) {
        printf("True. Two strings are different by one!\n");
    } else {
        printf("False. Two strings are not differ by one!\n");
    }
    return EXIT_SUCCESS;
}

bool differByOne(char * str1, char * str2) {
    bool isdifferbyOne = false;
    // changing one letter
    int changeOne = changeOneLetter(str1, str2);

    switch (changeOne) {
        case false:
            isdifferbyOne = false;
            break;
        case FIRST_STR_SHORTER_CODE:
            isdifferbyOne = addOrRemoveOne(str1, str2);
            break;
        case SECOND_STR_SHORTER_CODE:
            isdifferbyOne = addOrRemoveOne(str2, str1);
            break;
        default:
            isdifferbyOne = true;
            break;
    }

    return isdifferbyOne;
}

int changeOneLetter(char * str1, char * str2) {
    int i = 0;
    int diff = 0;
    while (*(str1+i) != '\0' && *(str2+i) != '\0') {
        if (*(str1+i) - *(str2+i)) {
            diff++;
        }
        i++;
    }
    
    char * strLong = str2;
    int changeOne = FIRST_STR_SHORTER_CODE;
    if (*(str1+i) != '\0') {
        // str2 is shorter
        strLong = str1;
        changeOne = SECOND_STR_SHORTER_CODE;
    }

    int lengthDiff = 0;
    while (*(strLong+i) != '\0') {
        lengthDiff += 1;
        i++;
    }

    if (lengthDiff == 0) {
        // same lengths and 1 diff in letter
        // str1 can change one letter to transform to str2
        if (diff == 1) {
            changeOne = true;
        } else {
            changeOne = false;
        }
    } else if (lengthDiff > 1) {
        changeOne = false;
    }
    return changeOne;
}

bool addOrRemoveOne(char * str1, char * str2) {
    bool addOne = true;
    int i1 = 0;
    int i2 = 0;

    while (*(str1+i1) != '\0') {
        if (*(str1+i1) - *(str2+i2) == 0) {
            i1++;
        } 
        i2++;
    }

    return addOne;
}