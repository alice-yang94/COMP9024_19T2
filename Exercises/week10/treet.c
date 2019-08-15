// basic.c: insert nodes into a BST, print the tree and free all nodes
#include <stdio.h>
#include <stdlib.h>

typedef struct node *Tree;
struct node {
   int data;
   Tree left;
   Tree right;
};
Tree revTree    (Tree);
void revTreeRec (Tree, Tree);
int sumTree     (Tree);

Tree insertTree (Tree, int);
Tree createTree (int);
void printTree  (Tree);

void sidePrintTree  (Tree);
void sidePrintTreeRec(Tree, int);

void freeTree   (Tree);


int main(int argc, char* argv[]) {
   Tree t;
   int returnStatus = EXIT_SUCCESS;
   if (argc > 1) {
       Tree t;
       int i;
       for (i=1; i<argc && !returnStatus; i++) {

           int node;
           int scanStatus = sscanf(argv[i], "%d", &node);
           
           if (scanStatus == 1) {
               if (i == 1) {
                   t = createTree(node);
               } else {
                   t = insertTree(t, node);
               } 
               
           } else {
               fprintf(stderr, "Error: incorrect input!\n");
               returnStatus = EXIT_FAILURE;
           }
       }
       if (returnStatus == EXIT_SUCCESS) {
           sidePrintTree(t);
           printf("Sum = %d\n", sumTree(t));
           printf("Tree in reverse\n");
           Tree reversedTree = revTree(t);
           if (reversedTree != NULL) {
               sidePrintTree(reversedTree);
               printf("Sum = %d\n", sumTree(reversedTree));
               freeTree(reversedTree); 
           }
       }
       freeTree(t);
   } else {
       fprintf(stderr, "Error: please enter tree nodes in command line!\n");
       returnStatus = EXIT_FAILURE;
   }
   return returnStatus;
}

Tree revTree(Tree t) {
    Tree reversedTree = NULL;
    if (t != NULL) {
        reversedTree = createTree(t->data);
        revTreeRec(reversedTree, t);
    } 
    return reversedTree;
}

void revTreeRec(Tree reversedTree, Tree t) {
    if (t->right != NULL) {
        reversedTree->left = createTree(t->right->data);
        revTreeRec(reversedTree->left, t->right);
    }
    if (t->left != NULL) {
        reversedTree->right = createTree(t->left->data);
        revTreeRec(reversedTree->right, t->left);
    }
}

int sumTree(Tree t) {
    int sum = 0;
    if (t != NULL) {
        sum = t->data + sumTree(t->left) + sumTree(t->right);
    }
    return sum;
}

Tree insertTree(Tree t, int v) {
   if (t == NULL) {
      t = createTree(v);
   }
   else {
      if (v < t->data) {
        t->left = insertTree (t->left, v);
      }
      else {
        t->right = insertTree (t->right, v);
      }
   }
   return t;
}

Tree createTree (int v) {
   Tree t = NULL;

   t = malloc (sizeof(struct node));
   if (t == NULL) {
      fprintf(stderr, "Memory is exhausted: exiting\n");
      exit(1);
   }
   t->data = v;
   t->left = NULL;
   t->right = NULL;
   return t;
}

void printTree(Tree t) { // not the final version
    if (t != NULL) {
        printTree (t->left);
        printf ("%d  ", t->data);
        printTree (t->right);
    }
    return;
}

void sidePrintTree(Tree t) {
    sidePrintTreeRec(t, 0);
}

void sidePrintTreeRec(Tree t, int level) {
    if (t != NULL) {
        sidePrintTreeRec(t->left, level+1);
        int i;
        for (i=0; i<level; i++) {
            putchar('\t');
        }
        printf("%d\n", t->data);
        sidePrintTreeRec(t->right, level+1);
    }
}

void freeTree(Tree t) { // free in postfix fashion
   if (t != NULL) {
      freeTree(t->left);
      freeTree(t->right);
      free(t);
   }
   return;
}