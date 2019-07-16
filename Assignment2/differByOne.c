/**
 * COMP9024 Assignment 2: Ordered Word Ladders
 * 
 * @author Wenke Yang
 * @email z5230655@student.unsw.edu.au
 * @create date 2019-07-15 22:18:34
 * @description 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
 * Returns: int - 0: True; 
 *                1: first str is shorter; 
 *                2: second str is shorter;
 *               -1: False. 
 * 
 * Check if one string can transform to another by 
 * changing one letter
*/
int changeOneLetter(char *, char *);

/**
 * Input: two null-terminated strings, str1 and str2
 *        str1 is shorter than str2 by 1.
 * Returns: bool 
 * 
 * Check if str1 can transform to str2 by adding one letter
*/
bool addOrRemoveOne(char *, char *);

int main(void) {
    char str1[100];
    char str2[100];
    printf("Enter the first string:\n");
    scanf("%s", str1);
    printf("Enter the second string:\n");
    scanf("%s", str2);
    if (differByOne(str1, str2)) {
        printf("True. Two strings are different by one!\n");
    } else {
        printf("False. Two strings cannot transform to another by one!\n");
    }
    return EXIT_SUCCESS;
}

bool differByOne(char * str1, char * str2) {
    bool isdifferbyOne = false;
    // changing one letter
    int changeOne = changeOneLetter(str1, str2);

    switch (changeOne) {
        case -1:
            isdifferbyOne = false;
            break;
        case 0:
            isdifferbyOne = true;
            break;
        case 1:
            isdifferbyOne = addOrRemoveOne(str1, str2);
            break;
        case 2:
            isdifferbyOne = addOrRemoveOne(str2, str1);
            break;
        default:
            break;
    }

    return isdifferbyOne;
}

int changeOneLetter(char * str1, char * str2) {
    int changeOne = 1;
    int i = 0;
    int diff = 0;
    while (*(str1+i) != '\0' && *(str2+i) != '\0') {
        if (*(str1+i) - *(str2+i)) {
            diff++;
        }
        i++;
    }
    int lengthDiff = 0;
    char * strLong = str2;
    if (*(str1+i) != '\0') {
        // 2 stands for str2 is shorter
        changeOne = 2;
        strLong = str1;
    }

    while (*(strLong+i) != '\0') {
        lengthDiff += 1;
        i++;
    }

    if (diff+lengthDiff <= 1) {
        // also True for case XXX AND XXXy
        // 0 stands for true, str1 can change one to str2
        changeOne = 0;
    } else if (lengthDiff > 1) {
        // -1 stands for false.
        changeOne = -1;
    }
    return changeOne;
}

bool addOrRemoveOne(char * str1, char * str2) {
    bool addOne = true;
    int i1 = 0;
    int i2 = 0;

    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);

    while (*(str1+i1) != '\0') {
        if (*(str1+i1) - *(str2+i2)) {
            i1++;
        } else if (i2-i1 > 1) {
            printf("i1: %d, i2: %d\n", i1, i2);
            addOne = false;
            break;
        }
        i2++;
    }

    return addOne;
}