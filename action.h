/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

#ifndef PROJETO1MC404_ACTION_H
#define PROJETO1MC404_ACTION_H

#include "action.c"

void execLine(line *lin, int *numlin, int *right, argnode *initmap,
              argnode *initsym, argnode *initlbl, int numlinin, int *error);

#endif //PROJETO1MC404_ACTION_H