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

    argnode *init = NULL, *tmp = NULL;

    in = fopen(files[1], "r");

    if(in == NULL){

        perror("Error");
        return 0;
    }

    if(argc == 3)
        outfile = 1;

    templine = calloc(200, sizeof(char));

    while(1){

        type = getLine(templine, in);
        //printf("%d\n", type);
        numlinin++;

        if(type == -1)
            continue;

        else if(!type)
            break;


        if(strct = idArgs(templine, numlinin)){

            printLine(strct);
            system("sleep 1s");
        }

        else{

            error = 1;
            free(templine);
            break;
        }

        for(cnt = 0; cnt < 200; cnt++)
            templine[cnt] = 0;

    }

    return 0;
}
