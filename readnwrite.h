/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

#ifndef READNWRITE_H_INCLUDED
#define READNWRITE_H_INCLUDED

#include "readnwrite.c"

int issym(char *arg, line *strct, int islbl);

line *idArgs(char *arg, int *numlin, int numlinlin);

int getLine(char *templine, FILE *in);

int numPlaces (int n);

int isHexNum(char *arg, line *strct);

int isDeciNum(char *arg, line *strct, int quomarks);

int idDir(char *arg, int cntdb, line *strct);

#endif /*READNWRITE_H_INCLUDED*/

