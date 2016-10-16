/*
   Projeto 1 - Montador para a arquitetura do computador IAS
   Nome: Eduardo Moreira Freitas de Souza
   RA: 166779
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "readnwrite.h"
#include "textnode.h"
#include "action.h"

int main (int argc, char **files){

    FILE *in, *out;
    int numlin = 0, type, numlinin = 0, error = 0, right = 0, outfile = 0, cnt;
    char *templine;
    line *strct;

    argnode *initmap = calloc(1, sizeof(argnode));
    argnode *initsym = calloc(1, sizeof(argnode));
    argnode *initlbl = calloc(1, sizeof(argnode));

    in = fopen(files[1], "r");

    if(in == NULL){

        perror("Error");
        return 0;
    }

    if(argc == 3)
        outfile = 1;

    templine = calloc(200, sizeof(char));

    while(!error){

        type = getLine(templine, in);
        numlinin++;

        if(type == -1)
            continue;

        else if(!type)
            break;


        if(strct = idArgs(templine, &numlin, numlinin)){

            //printLine(strct);
            execLine(strct, &numlin, &right, initmap, initsym, initlbl, numlinin, &error);
            //printNodes(initmap, initlbl, initsym);
            //system("sleep 0.5s");
        }

        else{

            error = 1;
            free(templine);
            break;
        }

        for(cnt = 0; cnt < 200; cnt++)
            templine[cnt] = 0;

    }

    free(templine);
    free(strct);

    fixSymLbl(initmap, initlbl, initsym);
    //printNodes(initmap, initlbl, initsym);
    printFinal(initmap);

    return 0;
}
