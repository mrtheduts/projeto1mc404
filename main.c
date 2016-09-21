/*
   Projeto 1 - Montador para a arquitetura do computador IAS
   Nome: Eduardo Moreira Freitas de Souza
   RA: 166779
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readnwrite.h"

int main (int argc, char **files){

    FILE *in, *out;

    in = fopen(files[0], "r");

    if(in == NULL){

        printf("Não foi possível abrir o arquivo %s\n", files[0]);
        return 1;
    }

    return 0;
}
