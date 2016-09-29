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
    char templine[65];

    in = fopen(files[0], "r");
    if(in == NULL){

    printf("Oi/n");
        printf("Não foi possível abrir o arquivo %s\n", files[0]);
//        perror("Error: ");
        return 1;
    }

    while(fgets(templine, 65, in) != NULL){


    }

    return 0;
}
