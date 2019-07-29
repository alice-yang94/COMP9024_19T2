// quack.h: an interface definition for a queue/stack
// Provided by Prof. Albert Nymeyer

#include <stdio.h>
#include <stdlib.h>

typedef struct node *Quack;

Quack createQuack(void);    // create and return Quack
Quack destroyQuack(Quack);  // remove the Quack 
void  push(int, Quack);     // put the given integer onto the top of the quack
void  qush(int, Quack);     // put the given integer onto the bottom of the quack
int   pop(Quack);           // pop and return the top element on the quack
int   isEmptyQuack(Quack);  // return 1 is Quack is empty, else 0
void  makeEmptyQuack(Quack);// remove all the elements on Quack
void  showQuack(Quack);     // print the contents of Quack, from the top down