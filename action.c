/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

void fixSymLbl(argnode *map, argnode *lbl, argnode *sym){

    argnode *nmap, *nlbl, *nsym;
    char arg[65], *tmp;
    int flagsym;

    nmap = map->nxt;

    while(nmap != NULL){

        flagsym = 0;

        if(nmap->label[0][0]){

            strcpy(arg, nmap->label[0]);

            nlbl = lbl->next[0];

            while (nlbl != NULL && strcmp(arg, nlbl->label[0]))
                nlbl = nlbl->next[0];


            if(nlbl == NULL) {

                nsym = sym->next[0];
                while(nsym != NULL && strcmp(arg, nsym->label[0]))
                    nsym = nsym->next[0];

                nlbl = nsym;
                flagsym = 1;
            }

            if(nmap->wfill){

                if(!strcmp(nmap->label[0], nlbl->label[0]) && flagsym){

                    tmp = calloc(10, sizeof(char));
                    sprintf(tmp, "%0.10X", nlbl->num);
                    memcpy(nmap->arg[0], tmp, 5);
                    tmp += 5;
                    memcpy(nmap->arg[1], tmp, 5);
                    tmp -= 5;
                }

                else{

                    tmp = calloc(10, sizeof(char));
                    sprintf(tmp, "%0.10X", nlbl->next[1]->numlin);
                    memcpy(nmap->arg[0], tmp, 5);
                    tmp += 5;
                    memcpy(nmap->arg[1], tmp, 5);
                    tmp -= 5;
                }
            }

            else {

                if((nmap->arg[0][0] == '0' && nmap->arg[0][1] == 'D') ||
                        (nmap->arg[0][0] == '0' && nmap->arg[0][1] == 'F') ||
                        (nmap->arg[0][0] == '1' && nmap->arg[0][1] == '2')){

                    if(nmap->arg[0][1] != 'F')
                        nmap->arg[0][1] += nlbl->right;

                    else{
                        nmap->arg[0][0] += '1';
                        nmap->arg[0][1] += '0';
                    }
                }

                tmp = calloc(5, sizeof(char));
                sprintf(tmp, "%0.5X", nlbl->next[1]->numlin);
                memcpy(tmp, nmap->arg[0], 2);
                memcpy(nmap->arg[0], tmp, 5);
            }

            free(tmp);
        }


        if(nmap->label[1][0]){

            strcpy(arg, nmap->label[1]);

            nlbl = lbl->next[0];

            while (nlbl != NULL && strcmp(arg, nlbl->label[0]))
                nlbl = nlbl->next[0];

            if((nmap->arg[1][0] == '0' && nmap->arg[1][1] == 'D') ||
               (nmap->arg[1][0] == '0' && nmap->arg[1][1] == 'F') ||
               (nmap->arg[1][0] == '1' && nmap->arg[1][1] == '2')){

                if(nmap->arg[1][1] != 'F')
                    nmap->arg[1][1] += nlbl->right;

                else{
                    nmap->arg[1][0] += '1';
                    nmap->arg[1][1] += '0';
                }
            }

            tmp = calloc(5, sizeof(char));
            sprintf(tmp, "%0.5X", nlbl->next[1]->numlin);
            memcpy(tmp, nmap->arg[1], 2);
            memcpy(nmap->arg[1], tmp, 5);
            free(tmp);
        }

        nmap = nmap->nxt;

    }

}

char *readyWordNum(line *lin){

    char *arg = calloc(10, sizeof(char));

    sprintf(arg, "%0.10X", lin->num);

    return arg;
}

char *readyWordWfill(line *lin){

    char *arg = calloc(10, sizeof(char));

    sprintf(arg, "%0.10X", lin->numwfill);

    return arg;
}

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
    int initwfill, endwfill;
    char *tmp;

    if(lin->inst){

        if(!*right)
            insertElem(initmap, lin, *numlin, 1, NULL);

        node = searchElem(initmap, *numlin, NULL, 1);

        if(!lin->symbol)
            strcpy(node->arg[*right], readyHalfWord(lin));


        else{

            sprintf(node->arg[*right], "%0.2X", lin->inst);
            strcpy(node->label[*right], lin->sym);
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

            if(searchElem(initsym, *numlin, lin->sym, 2)){

                printf("ERROR on line %d\nRedefinicao de simbolo.\n", numlinin);
                free(lin);
                *error = 1;
                return;
            }

            else{

                insertElem(initsym, lin, *numlin, 3, NULL);
            }

            return;
        }

        else if(lin->dir == 2){

            *numlin = lin->num;
            return;
        }

        else if(lin->dir == 3){

            while((*numlin)%lin->num && (*numlin) < 1024)
                (*numlin)++;

            if(*numlin == 1024){

                printf("ERROR on line %d\n.align tem argumento que ultrapassa mapa de memoria.\n", numlinin);
                free(lin);
                *error = 1;
                return;
            }

            *right = 0;

            return;
        }

        else if(lin->dir == 4){


            if(*right){

                printf("ERROR on line %d\nWfill comecando do lado direito.\n", numlinin);
                free(lin);
                *error = 1;
                return;
            }

            else{

                initwfill = *numlin;
                endwfill = lin->num;


                if(node = searchElem(initmap, *numlin, NULL, 1)){

                    (*numlin)++;
                    endwfill--;
                }

                while(endwfill){

                    insertElem(initmap, lin, *numlin, 1, NULL);
                    endwfill--;
                    (*numlin)++;
                }

                node = searchElem(initmap, initwfill, NULL, 1);

                if(!lin->symbol){
                    for(endwfill = 0; endwfill < lin->num; endwfill++){

                        tmp = readyWordWfill(lin);
                        memcpy(node->arg[0], tmp, 5);
                        tmp += 5;
                        memcpy(node->arg[1], tmp, 5);
                        node = node->nxt;
                        free(tmp - 5);
                    }
                }

                else{
                    for(endwfill = 0; endwfill < lin->num; endwfill++){

                        strcpy(node->label[0], lin->sym);
                        node->wfill = 1;
                        node = node->nxt;
                    }

                }

                *right = 0;
                return;
            }

        }

        if(lin->dir == 5){

            if(*right){

                printf("ERROR on line %d\nWord do lado direito.\n", numlinin);
                free(lin);
                *error = 1;
                return;
            }

            if(node = searchElem(initmap, *numlin, NULL, 1));

            else{

                insertElem(initmap, lin, *numlin, 1, NULL);
                node = searchElem(initmap, *numlin, NULL, 1);
            }

            node->wfill = 1;

            if(!lin->symbol){

                tmp = readyWordNum(lin);
                memcpy(node->arg[0], tmp, 5);
                tmp += 5;
                memcpy(node->arg[1], tmp, 5);
                free(tmp - 5);
            }

            else
                strcpy(node->label[0], lin->sym);

            (*numlin)++;
            return;
        }
    }


    if(lin->dir || lin->inst){
        if (*right) {

            (*numlin)++;
            *right = 0;
        } else
            *right = 1;
    }

}