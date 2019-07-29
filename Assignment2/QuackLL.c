// QuackLL.c: a linked-list-based implementation of a quack
// Provided by Prof. Albert Nymeyer

#include "Quack.h"
#include <limits.h>

#define MARKERDATA INT_MAX // dummy data

struct node {
   int data;
   struct node *next;
};

Quack createQuack(void) {
   Quack marker;
   marker = malloc(sizeof(struct node));
   if (marker == NULL) {
      fprintf (stderr, "createQuack: no memory, aborting\n");
      exit(1);
   }
   marker->data = MARKERDATA; // should never be used
   marker->next = NULL;
   return marker;
}

void push(int data, Quack qs) {
   Quack newnode;
   if (qs == NULL) {
      fprintf(stderr, "push: quack not initialised\n");
   }
   else {
      newnode = malloc(sizeof(struct node));
      if (newnode == NULL) {
         fprintf(stderr, "push: no memory, aborting\n");
         exit(1);
      }
      newnode->data = data;
      newnode->next = qs->next;
      qs->next = newnode;
   }
   return;
}

void qush(int data, Quack que) { // adds data to the end of linked list
   Quack newnode;
   Quack endnode;
   if (que == NULL) {
      fprintf(stderr, "qush: quack not initialised\n");
   }
   else {
      newnode = malloc(sizeof(struct node));
      if (newnode == NULL) {
         fprintf(stderr, "qush: no memory, aborting\n");
         exit(1);
      }
      newnode->data = data;
      newnode->next = NULL;           // = bottom of quack = end of linked list
      endnode = que;
      while (endnode->next != NULL) { // go to the end of the list
         endnode = endnode->next;
      }
      endnode->next = newnode;        // newnode is the new end of list
   }
   return;
}

int pop(Quack qs) {
   int retval = 0;
   if (qs == NULL) {
      fprintf(stderr, "pop: quack not initialised\n");
   }
   else {
      if (isEmptyQuack(qs)) {
         fprintf(stderr, "pop: quack underflow\n");
      }
      else {
         Quack topnode = qs->next; // top dummy node is always there
         retval = topnode->data;
         qs->next = topnode->next;
         free(topnode);
      }
   }
   return retval;
}

Quack destroyQuack(Quack qs) { // remove the Quack  and returns NULL
   if (qs == NULL) {
      fprintf(stderr, "destroyQuack: quack not initialised\n");
   }
   else {
      Quack ptr = qs->next;
      while (ptr != NULL) {
         Quack tmp = ptr->next;
         free(ptr);
         ptr = tmp;
      }
      free(qs);
   }
   return NULL;
}

void makeEmptyQuack(Quack qs) {
   if (qs == NULL)
      fprintf(stderr, "makeEmptyQuack: quack not initialised\n");
   else {
      while (!isEmptyQuack(qs)) {
         pop(qs);
      }
   }
   return;
}

int isEmptyQuack(Quack qs) {
   int empty = 0;
   if (qs == NULL) {
      fprintf(stderr, "isEmptyQuack: quack not initialised\n");
   }
   else {
      empty = qs->next == NULL;
   }
   return empty;
}

void showQuack(Quack qs) {
   if (qs == NULL) {
      fprintf(stderr, "showQuack: quack not initialised\n");
   }
   else {
      printf("Quack: ");
      if (qs->next == NULL) {
         printf("<< >>\n");
      }
      else {
         printf("<<");                 // start with <<
         qs = qs->next;                // step over the marker link
         while (qs->next != NULL) {
            printf("%d, ", qs->data);  // print each element
            qs = qs->next;
         }
         printf("%d>>\n", qs->data);    // last element ends with >>
      }
   }
   return;
}