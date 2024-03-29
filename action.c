/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "textnode.h"

void fixSymLbl(argnode *map, argnode *lbl, argnode *sym, FILE *out, int *error){

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

            if(nlbl == NULL){

                if(out == NULL){

                    printf("ERROR on line %d\nSYM/LABEL não declarado.\n", nmap->numlinin[0]);
                    *error = 1;
                    return;
                }

                else{

                    fprintf(out, "ERROR on line %d\nSYM/LABEL não declarado.\n", nmap->numlinin[0]);
                    *error = 1;
                    return;
                }
            }

            if(nmap->wfill){

                if(!strcmp(nmap->label[0], nlbl->label[0]) && flagsym){

                    tmp = calloc(10, sizeof(char));
                    sprintf(tmp, "%.10X", (unsigned int) nlbl->num);
                    memcpy(nmap->arg[0], tmp, 5);
                    tmp += 5;
                    memcpy(nmap->arg[1], tmp, 5);
                    tmp -= 5;
                }

                else{

                    tmp = calloc(10, sizeof(char));
                    sprintf(tmp, "%.10X", nlbl->next[1]->numlin);
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

                    else if(nlbl->right){
                        nmap->arg[0][0] = '1';
                        nmap->arg[0][1] = '0';
                    }
                }

                tmp = calloc(5, sizeof(char));
                sprintf(tmp, "%.5X", nlbl->next[1]->numlin);
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

            if(nlbl == NULL){

                if(out == NULL){

                    printf("ERROR on line %d\nSYM/LABEL não declarado.\n", nmap->numlinin[0]);
                    *error = 1;
                    return;
                }

                else{

                    fprintf(out, "ERROR on line %d\nSYM/LABEL não declarado.\n", nmap->numlinin[0]);
                    *error = 1;
                    return;
                }
            }

            if((nmap->arg[1][0] == '0' && nmap->arg[1][1] == 'D') ||
               (nmap->arg[1][0] == '0' && nmap->arg[1][1] == 'F') ||
               (nmap->arg[1][0] == '1' && nmap->arg[1][1] == '2')){

                if(nmap->arg[1][1] != 'F')
                    nmap->arg[1][1] += nlbl->right;

                else if(nlbl->right){
                    nmap->arg[1][0] = '1';
                    nmap->arg[1][1] = '0';
                }
            }

            tmp = calloc(5, sizeof(char));
            sprintf(tmp, "%.5X", nlbl->next[1]->numlin);
            memcpy(tmp, nmap->arg[1], 2);
            memcpy(nmap->arg[1], tmp, 5);
            free(tmp);
        }

        nmap = nmap->nxt;

    }

}

char *readyWordNum(line *lin){

    char *arg = calloc(10, sizeof(char));

    sprintf(arg, "%.10X", (unsigned int) lin->num);

    return arg;
}

char *readyWordWfill(line *lin){

    char *arg = calloc(10, sizeof(char));

    sprintf(arg, "%.10X", (unsigned int) lin->numwfill);

    return arg;
}

char *readyHalfWord(line *lin){

    char *arg = calloc(5, sizeof(char));

    sprintf(arg, "%.2X", lin->inst);
    arg += 2;

    sprintf(arg, "%.3X", (unsigned int) lin->num);
    arg -= 2;

    //printf("RHW %s\n", arg);

    return arg;

}

void execLine(line *lin, int *numlin, int *right, argnode *initmap,
              argnode *initsym, argnode *initlbl, int numlinin, int *error, FILE *out){

    argnode *node = NULL;
    int initwfill, endwfill;
    char *tmp;

    //printNodes(initmap, initlbl, initsym);

    if(*numlin > 1023){

        if(out == NULL){

            printf("ERROR on line %d\nLimite do mapa de memoria ultrapassado.\n", *numlin);
            free(lin);
            *error = 1;
            return;
        }

        else{

            fprintf(out, "ERROR on line %d\nLimite do mapa de memoria ultrapassado.\n", *numlin);
            free(lin);
            *error = 1;
            return;
        }
    }

    if(lin->inst){

        if(!*right)
            insertElem(initmap, lin, *numlin, 1, NULL);

        node = searchElem(initmap, *numlin, NULL, 1);


        if(!lin->symbol)
            strcpy(node->arg[*right], readyHalfWord(lin));


        else{

            sprintf(node->arg[*right], "%.2X", lin->inst);
            strcpy(node->label[*right], lin->sym);
        }

        node->numlinin[*right] = lin->line;
        //printf("%s %s\n", node->arg[0], node->arg[1]);

    }

    if(lin->label) {

        lin->lbl[strlen(lin->lbl) - 1] = 0;

        if(searchElem(initlbl, *numlin, lin->lbl, 2)){

            if(out == NULL)
                printf("ERROR on line %d\nRedefinicao de rotulo.\n", numlinin);
            else
                fprintf(out, "ERROR on line %d\nRedefinicao de rotulo.\n", numlinin);

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
            node->numlinin[*right] = lin->line;
        }

    }

    if(lin->dir){

        if(lin->dir == 1){

            if(searchElem(initsym, *numlin, lin->sym, 2)){

                if(out == NULL)
                    printf("ERROR on line %d\nRedefinicao de simbolo.\n", numlinin);
                else
                    fprintf(out, "ERROR on line %d\nRedefinicao de simbolo.\n", numlinin);

                free(lin);
                *error = 1;
                return;
            }

            else{

                insertElem(initsym, lin, *numlin, 3, NULL);
                node = searchElem(initsym, *numlin, lin->sym, 2);
                node->numlinin[*right] = lin->line;
            }

            return;
        }

        else if(lin->dir == 2){

            *numlin = lin->num;
            *right = 0;
            return;
        }

        else if(lin->dir == 3){

            if(*right)
                (*numlin)++;

            while((*numlin)%lin->num && (*numlin) < 1024)
                (*numlin)++;


            if(*numlin == 1024){

                if(out == NULL)
                    printf("ERROR on line %d\n.align tem argumento que ultrapassa mapa de memoria.\n", numlinin);
                else
                    fprintf(out, "ERROR on line %d\n.align tem argumento que ultrapassa mapa de memoria.\n", numlinin);

                free(lin);
                *error = 1;
                return;
            }

            *right = 0;

            return;
        }

        else if(lin->dir == 4){


            if(*right){

                if(out == NULL)
                    printf("ERROR on line %d\nWfill comecando do lado direito.\n", numlinin);
                else
                    fprintf(out, "ERROR on line %d\nWfill comecando do lado direito.\n", numlinin);

                free(lin);
                *error = 1;
                return;
            }

            else{

                initwfill = *numlin;
                endwfill = lin->num;


                if((node = searchElem(initmap, *numlin, NULL, 1))){

                    (*numlin)++;
                    endwfill--;
                }

                while(endwfill){

                    insertElem(initmap, lin, *numlin, 1, NULL);
                    endwfill--;
                    (*numlin)++;
                }

                node = searchElem(initmap, initwfill, NULL, 1);
                node->numlinin[*right] = lin->line;

                if(!lin->symbol){
                    for(endwfill = 0; endwfill < lin->num; endwfill++){

                        tmp = readyWordWfill(lin);
                        memcpy(node->arg[0], tmp, 5);
                        tmp += 5;
                        memcpy(node->arg[1], tmp, 5);
                        node->numlinin[*right] = lin->line;
                        node = node->nxt;
                        free(tmp - 5);
                    }
                }

                else{
                    for(endwfill = 0; endwfill < lin->num; endwfill++){

                        strcpy(node->label[0], lin->sym);
                        node->wfill = 1;
                        node->numlinin[*right] = lin->line;
                        node = node->nxt;
                    }

                }

                *right = 0;
                return;
            }

        }

        if(lin->dir == 5){

            if(*right){

                if(out == NULL)
                    printf("ERROR on line %d\nWord do lado direito.\n", numlinin);
                else
                    fprintf(out, "ERROR on line %d\nWord do lado direito.\n", numlinin);

                free(lin);
                *error = 1;
                return;
            }

            if((node = searchElem(initmap, *numlin, NULL, 1)));

            else{

                insertElem(initmap, lin, *numlin, 1, NULL);
                node = searchElem(initmap, *numlin, NULL, 1);
            }

            node->wfill = 1;
            node->numlinin[*right] = lin->line;

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