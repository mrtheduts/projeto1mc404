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
    int numlin = 0, type;
    char *templine, error = 0, right = 0;

    argnode *init = NULL, *tmp = NULL;

    in = fopen(files[1], "r");

    if(in == NULL){

        perror("Error");
        return 0;
    }

    templine = calloc(85, sizeof(char));

    do{

        type = getLine(templine, in);
        //printf("%d\n", type);

        if(type == -1)
            continue;
        else if(!type)
            break;

      //  type = idArgs(templine, &numlin);
/*
        if(init == NULL)
            init = newNode(numlin);

        else {

            tmp = init;

            while (tmp->next != NULL)
                tmp = tmp->next;

            tmp->next = newNode(numlin);
        }
*/
    }while(type);

    return 0;
}
