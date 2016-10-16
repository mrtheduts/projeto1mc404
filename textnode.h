/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

#ifndef TEXTNODE_H_INCLUDED
#define TEXTNODE_H_INCLUDED

#include "textnode.c"

/*Cria um novo no ja identificado pelo numero da linha*/
argnode* newNode (int nl);

argnode *searchElem(argnode *node, int lin, char *arg, int type);

void insertElem(argnode *node, line *lin, int numlin, int type, argnode *dest);

/*Desaloca toda a lista*/
//void destroyLine(argnode *node);

#endif /*TEXTNODE_H_INCLUDED*/
