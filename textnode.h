/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

#ifndef TEXTNODE_H_INCLUDED
#define TEXTNODE_H_INCLUDED

//#include "textnode.c"

#include "readnwrite.h"

typedef struct ArgNode{

    int type;
    int right;
    int wfill;
    int sym;
    int numlinin[2];
    int numlin;
    char label[2][65];

    char arg[2][6];
    unsigned long int num;

    struct ArgNode *nxt;
    struct ArgNode *next[2];


}argnode;


void printNodes(argnode *node1, argnode *node2, argnode *node3);

void freeNodes(argnode *node, int type);

void printFinal(argnode *init, FILE *out);

argnode *searchElem(argnode *node, int lin, char *arg, int type);

void insertElem(argnode *node, line *lin, int numlin, int type, argnode *dest);

#endif /*TEXTNODE_H_INCLUDED*/
