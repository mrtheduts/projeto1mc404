/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

#ifndef PROJETO1MC404_ACTION_H
#define PROJETO1MC404_ACTION_H

//#include "action.c"
#include "textnode.h"

void fixSymLbl(argnode *map, argnode *lbl, argnode *sym, FILE *out, int *error);

char *readyWordNum(line *lin);

char *readyWordWfill(line *lin);

char *readyHalfWord(line *lin);

void execLine(line *lin, int *numlin, int *right, argnode *initmap,
              argnode *initsym, argnode *initlbl, int numlinin, int *error, FILE *out);

#endif //PROJETO1MC404_ACTION_H
