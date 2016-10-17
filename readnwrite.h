/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

#ifndef READNWRITE_H_INCLUDED
#define READNWRITE_H_INCLUDED

//#include "readnwrite.c"

typedef struct Line{

    int dir;
    int label;
    int symbol;
    int inst;
    int line;
    unsigned long int num;
    int negative;
    int hex;
    char lbl[65];
    char sym[65];
    unsigned long int numwfill;
    int negativewfill;

}line;

void printLine(line *strct);

int issym(char *arg, line *strct, int islbl);

line *idArgs(char *arg, int *numlin, int numlinlin, FILE *out);

int getLine(char *templine, FILE *in);

int numPlaces (int n);

int isHexNum(char *arg, line *strct, int quomarks);

int isDeciNum(char *arg, line *strct, int quomarks);

int idDir(char *arg, int cntdb, line *strct);

int getLine(char *templine, FILE *in);

#endif /*READNWRITE_H_INCLUDED*/

