/*
   Projeto 1 - Montador para a arquitetura do computador IAS
   Nome: Eduardo Moreira Freitas de Souza
   RA: 166779
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readnwrite.h"
#include "textnode.h"

int main (int argc, char **files){

    FILE *in, *out;
    int numlin = 0;
    char *templine;
    argnode *init = NULL;

    in = fopen(files[1], "r");

    if(in == NULL){

        perror("Error: ");
        return 1;
    }

    templine = malloc(65*sizeof(char));

    while(fgets(templine, 65, in) != NULL){

        templine = idArgs(templine, numlin);

        if(init == NULL){

        }

        else
            init = newNode(numlin);
        

        numlin++;
    }

    return 0;
}
