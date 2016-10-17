/*
   Projeto 1 - Montador para a arquitetura do computador IAS
   Nome: Eduardo Moreira Freitas de Souza
   RA: 166779
*/

#include <stdio.h>
#include <stdlib.h>

#include "action.h"

int main (int argc, char **files){

    FILE *in, *out = NULL;
    int numlin = 0, type, numlinin = 0, error = 0, right = 0, cnt;
    char *templine;
    line *strct = NULL;

    argnode *initmap = calloc(1, sizeof(argnode));
    argnode *initsym = calloc(1, sizeof(argnode));
    argnode *initlbl = calloc(1, sizeof(argnode));

    in = fopen(files[1], "r");

    if(in == NULL){

        perror("Error");
        return 0;
    }

    if(argc == 3)
        out = fopen(files[2], "w");

    templine = calloc(200, sizeof(char));

    while(!error){

        type = getLine(templine, in);
        numlinin++;

        if(type == -1)
            continue;

        else if(!type)
            break;

        strct = idArgs(templine, &numlin, numlinin, out);

        if(strct != NULL){

            //printLine(strct);
            execLine(strct, &numlin, &right, initmap, initsym, initlbl, numlinin, &error, out);
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

    if(strct != NULL) {
        free(strct);
    }


    //printNodes(initmap, initlbl, initsym);


    fixSymLbl(initmap, initlbl, initsym, out, &error);
    //printNodes(initmap, initlbl, initsym);

    if(!error)
        printFinal(initmap, out);


    freeNodes(initmap, 1);
    freeNodes(initlbl, 2);
    freeNodes(initsym, 2);

    return 0;
}
