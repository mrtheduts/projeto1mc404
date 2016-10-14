/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

#ifndef READNWRITE_H_INCLUDED
#define READNWRITE_H_INCLUDED

#include "readnwrite.c"

line *idArgs(char *arg, int *numlin, char *right, int numlinlin);

int getLine(char *templine, FILE *in);

#endif /*READNWRITE_H_INCLUDED*/

