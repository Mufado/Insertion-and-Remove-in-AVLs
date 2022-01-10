#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

typedef struct no
{
    int value;
    int bal;
    struct no *esq;
    struct no *dir;
}node;

void printInOrder(node **pt);

void printPreOrder(node **pt);

void freePosOrder (node **pt);

node* initializeNode(int value);

bool rotationRight(node **pt, bool *h);

bool rotationLeft(node **pt, bool *h);

bool insertAVL(int value, node **pt, bool *h);

bool rotationRightR(node **pt, bool *h);

bool rotationLeftR(node **pt, bool *h);

void balance(node **pt, char D, bool *h);

void swapNodes(node **pt, node **s);

bool removeAVL(int value, node **pt, bool *h);

int heightAVL(node **pt);

int numberNodesAVL(node **pt);

#endif // FUNCTIONS_H_INCLUDED
