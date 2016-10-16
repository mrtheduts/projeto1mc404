/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

char *readyHalfWord(line *lin){

    char *arg = calloc(5, sizeof(char));

    sprintf(arg, "%0.2X", lin->inst);
    arg += 2;

    sprintf(arg, "%0.3X", lin->num);
    arg -= 2;

    return arg;

}

void execLine(line *lin, int *numlin, int *right, argnode *initmap,
              argnode *initsym, argnode *initlbl, int numlinin, int *error){

    argnode *node = NULL;

    if(lin->inst){

        if(!*right)
            insertElem(initmap, lin, *numlin, 1, NULL);

        node = searchElem(initmap, *numlin, NULL, 1);

        if(!lin->symbol) {
            strcpy(node->arg[*right], readyHalfWord(lin));
            printf("%0.3X %s %s\n", node->numlin, node->arg[0], node->arg[1]);
        }

        else{

            sprintf(node->arg[*right], "%0.2X", lin->inst);
            strcpy(node->label, lin->sym);
            printf("%0.3X %s %s\n", node->numlin, node->arg[0], node->label);
        }



    }

    if(lin->label) {

        lin->lbl[strlen(lin->lbl) - 1] = 0;

        if(searchElem(initlbl, *numlin, lin->lbl, 2)){

            printf("ERROR on line %d\nRedefinicao de rotulo.\n", numlinin);
            free(lin);
            *error = 1;
            return;
        }

        else{

            insertElem(initlbl, lin, *numlin, 2, node);
            node = searchElem(initmap, *numlin, NULL, 1);

            if(node == NULL)
                insertElem(initmap, lin, *numlin, 1, NULL);

            node = searchElem(initlbl, *numlin, lin->lbl, 2);
            node->next[1] = searchElem(initmap, *numlin, NULL, 1);
            node->right = *right;
        }

    }

    if(lin->dir){

        if(lin->dir == 1){


        }
    }

    if(*right) {

        (*numlin)++;
        *right = 0;
    }
    else
        *right = 1;

}