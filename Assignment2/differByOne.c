/**
 * COMP9024 Assignment 2: Ordered Word Ladders version 2 
 * (using string.h)
 * 
 * @author Wenke Yang
 * @email z5230655@student.unsw.edu.au
 * @create date 2019-07-15 22:18:34
 * @description 
*/

#include "differByOne.h"

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