#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no
{
    int value;
    int bal;
    struct no *esq;
    struct no *dir;
}node;

void printInOrder(node **pt)
{
    if ((*pt)->esq != NULL) {
        printInOrder(&((*pt)->esq));
    }
    printf(" %d |", (*pt)->value);
    if ((*pt)->dir != NULL) {
        printInOrder(&((*pt)->dir));
    }
}

void printPreOrder(node **pt)
{
    printf(" %d |", (*pt)->value);
    if ((*pt)->esq != NULL) {
        printPreOrder(&((*pt)->esq));
    }
    if ((*pt)->dir != NULL) {
        printPreOrder(&((*pt)->dir));
    }
}

void freePosOrder (node **pt)
{
    if ((*pt)->esq != NULL) {
        freePosOrder(&((*pt)->esq));
    }
    if ((*pt)->dir != NULL) {
        freePosOrder(&((*pt)->dir));
    }
    free(*pt);
    *pt = NULL;
}

node* initializeNode(int value)
{
    node *newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    newNode->bal = 0;
    newNode->esq = NULL;
    newNode->dir = NULL;
    return newNode;
}

bool rotationRight(node **pt, bool *h)
{
    node *ptu = (*pt)->esq;
    if (ptu->bal == -1) {
        (*pt)->esq = ptu->dir;
        ptu->dir = *pt;
        *pt = ptu;
        (*pt)->dir->bal = 0;
    } else {
        node *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = *pt;
        switch (ptv->bal) {
        case 1:
            (*pt)->bal = 0;
            ptu->bal = -1;
            break;
        case 0:
            (*pt)->bal = 0;  //
            ptu->bal = 0;    // Alteração aqui
            break;           //
        case -1:
            (*pt)->bal = 1;
            ptu->bal = 0;
        }
        *pt = ptv;
    }
    (*pt)->bal = 0;
    *h = false;
    return *h;
}

bool rotationLeft(node **pt, bool *h)
{
    node *ptu = (*pt)->dir;
    if (ptu->bal == 1) {
       (*pt)->dir = ptu->esq;
        ptu->esq = *pt;
        *pt = ptu;
        (*pt)->esq->bal = 0;
    } else {
        node *ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = *pt;
        switch (ptv->bal) {
        case -1:
            (*pt)->bal = 0;
            ptu->bal = 1;
            break;
        case 0:
            (*pt)->bal = 0;  //
            ptu->bal = 0;    // Alteração aqui
            break;           //
        case 1:
            (*pt)->bal = -1;
            ptu->bal = 0;
        }
        *pt = ptv;
    }
    (*pt)->bal = 0;
    *h = false;
    return *h;
}

bool insertAVL(int value, node **pt, bool *h)
{
    *h = true;  // Começar sempre com h sendo verdadeiro
    if (*pt == NULL) {
        *pt = initializeNode(value);
        return true;
    } else {
        if (value == (*pt)->value) {
            *h = false;
            return false;
        }
        if (value < (*pt)->value) {
            if (!insertAVL(value, &((*pt)->esq), &(*h))){
                return false;
            }
            if (*h == true) {
                switch ((*pt)->bal) {
                case 1:
                    (*pt)->bal = 0;
                    *h = false;
                    break;
                case 0:
                    (*pt)->bal = -1;
                    break;
                case -1:
                    rotationRight(&(*pt), &(*h));
                    break;
                }
            }
        } else {
            if (!insertAVL(value, &((*pt)->dir), &(*h))){
                return false;
            }
            if (*h == true) {
                switch ((*pt)->bal) {
                case -1:
                    (*pt)->bal = 0;
                    *h = false;
                    break;
                case 0:
                    (*pt)->bal = 1;
                    break;
                case 1:
                    rotationLeft(&(*pt), &(*h));
                    break;
                }
            }
        }
        return true;
    }
}

bool rotationRightR(node **pt, bool *h)
{
    node *ptu = (*pt)->esq;
    if (ptu->bal <= 0) {
        (*pt)->esq = ptu->dir;
        ptu->dir = *pt;
        *pt = ptu;
        if (ptu->bal == -1) {
            ptu->bal = 0;
            (*pt)->dir->bal = 0;
            *h = true;
        } else {
            ptu->bal = 1;
            (*pt)->dir->bal = -1;
            *h = false;
        }
    } else {
        node *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = *pt;
        *pt = ptv;
        switch (ptv->bal) {
        case -1:
            ptu->bal = 0;
            (*pt)->dir->bal = 1;
            break;
        case 0:
            ptu->bal = 0;
            (*pt)->dir->bal = 0;
            break;
        case 1:
            ptu->bal = -1;
            (*pt)->dir->bal = 0;
            break;
        }
        (*pt)->bal = 0;
        *h = true;
    }
    return *h;
}

bool rotationLeftR(node **pt, bool *h)
{
    node *ptu = (*pt)->dir;
    if (ptu->bal >= 0) {
        (*pt)->dir = ptu->esq;
        ptu->esq = *pt;
        (*pt) = ptu;
        if (ptu->bal == 1) {
            ptu->bal = 0;
            (*pt)->esq->bal = 0;
            *h = true;
        } else {
            ptu->bal = -1;
            (*pt)->esq->bal = 1;
            *h = false;
        }
    } else {
        node *ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = *pt;
        *pt = ptv;
        switch (ptv->bal) {
        case -1:
            ptu->bal = 1;
            (*pt)->esq->bal = 0;
            break;
        case 0:
            ptu->bal = 0;
            (*pt)->esq->bal = 0;
            break;
        case 1:
            ptu->bal = 0;
            (*pt)->esq->bal = -1;
            break;
        }
        (*pt)->bal = 0;
        *h = true;
    }
    return *h;
}

void balance(node **pt, char D, bool *h)
{
    if (*h == true) {
        if (D == 'R') {
            switch ((*pt)->bal) {
            case 1:
                (*pt)->bal = 0;
                break;
            case 0:
                (*pt)->bal = -1;
                *h = false;
                break;
            case -1:
                rotationRightR(&(*pt), &(*h));
                break;
            }
        } else {
            switch ((*pt)->bal) {
            case -1:
                (*pt)->bal = 0;
                break;
            case 0:
                (*pt)->bal = 1;
                *h = false;
                break;
            case 1:
                rotationLeftR(&(*pt), &(*h));
                break;
            }
        }
    }
}

void swapNodes(node **pt, node **s)
{
    node *cloneS = (node*)(malloc(sizeof(node)));
    cloneS->bal = (*s)->bal;
    cloneS->value = (*s)->value;    // Não será utilizado
    cloneS->dir = (*s)->dir;
    cloneS->esq = (*s)->esq;
    (*s)->esq = (*pt)->esq;
    (*s)->dir = (*pt)->dir;
    (*s)->bal = (*pt)->bal;
    (*pt)->esq = cloneS->esq;
    (*pt)->dir = cloneS->dir;
    (*pt)->bal = cloneS->bal;
    free(cloneS);
    cloneS = *s;
    *s = *pt;
    *pt = cloneS;
    cloneS = NULL;
}

bool removeAVL(int value, node **pt, bool *h)
{
    if ((*pt) == NULL) {
        printf("\nElemento %d nao existe nesta arvore\n", value);
        *h = false;
        return false;
    } else {
        if (value < (*pt)->value) {
            if (!removeAVL(value, &((*pt)->esq), &(*h))) {
                return false;
            }
            balance(&(*pt), 'L', &(*h));
        } else {
            if (value > (*pt)->value) {
                if (!removeAVL(value, &((*pt)->dir), &(*h))) {
                    return false;
                }
                balance(&(*pt), 'R', &(*h));
            } else {
                node *aux = *pt;
                if ((*pt)->esq == NULL) {
                    *pt = (*pt)->dir;
                    *h = true;
                } else {
                    if ((*pt)->dir == NULL) {
                        *pt = (*pt)->esq;
                        *h = true;
                    } else {
                        node *s = (*pt)->dir;
                        if (s->esq == NULL) {
                            s->esq = (*pt)->esq;
                            s->bal = (*pt)->bal;
                            *pt = s;
                            *h = true;
                        } else {
                            node *DadS;
                            while (s->esq != NULL) {
                                DadS = s;
                                s = s->esq;
                            }
                            swapNodes(&(*pt), &(DadS->esq));
                            removeAVL(value, &((*pt)->dir), &(*h));
                        }
                        balance(&(*pt), 'R', &(*h));
                    }
                }
                free(aux);
            }
        }
        return true;
    }
}

int heightAVL(node **pt)
{
    if (*pt != NULL) {
        int heightLeft = heightAVL(&((*pt)->esq));
        int heightRight = heightAVL(&((*pt)->dir));
        if ((*pt)->bal != heightRight - heightLeft) {
            printf("\nIncorrect bal: NODE(%6d) [expected %2d received %2d]", (*pt)->value, (heightRight - heightLeft), (*pt)->bal);
        }
        if (heightLeft > heightRight) {
            return heightLeft + 1;
        } else {
            return heightRight + 1;
        }
    } else {
        return 0;
    }
}

int numberNodesAVL(node **pt)
{
    if (*pt == NULL) {
        return 0;
    }
    return numberNodesAVL(&((*pt)->esq)) + numberNodesAVL(&((*pt)->dir)) + 1;
}
