/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

typedef struct ArgNode{

    int type;
    int right;
    int wfill;
    int sym;

    int numlin;
    char label[2][65];


    union{

        char arg[2][6];
        unsigned long int num;
    };

    union{

        struct ArgNode *nxt;
        struct ArgNode *next[2];
    };

}argnode;

void printNodes(argnode *node1, argnode *node2, argnode *node3){

    while(node1->nxt != NULL){
        printf("NumLin %d | %s %s | %s %s | %d\n", node1->nxt->numlin,
        node1->nxt->label[0], node1->nxt->label[1],  node1->nxt->arg[0], node1->nxt->arg[1],
        node1->nxt->num);

        node1 = node1->nxt;
    }
    printf("//\n");
    while(node2->next[0] != NULL){
        printf("%s | %d\n", node2->next[0]->label[0], node2->next[0]->next[1]->numlin);
        node2 = node2->next[0];
    }
    printf("//\n");
    while(node3->next[0] != NULL){
        printf("%s | %d\n", node3->next[0]->label[0], node3->next[0]->num);
        node3 = node3->next[0];
    }


}

void freeNodes(argnode *node, int type){

    if(type == 1){

        if(node == NULL)
            return

        freeNodes(node->nxt, 1);
        free(node);
    }

    else if(type == 2){

        if(node == NULL)
            return;

        freeNodes(node->next[0], 2);
        free(node);
    }
}

void printFinal(argnode *init, FILE *out){

    init = init->nxt;


    if(out != NULL){

        while(init != NULL){

            if(strcmp(init->arg[0], "00000") || strcmp(init->arg[1], "00000") ||
               init->wfill)
                fprintf(out, "%0.3X %c%c %c%c%c %c%c %c%c%c\n", init->numlin,
                       init->arg[0][0], init->arg[0][1], init->arg[0][2],
                       init->arg[0][3], init->arg[0][4], init->arg[1][0],
                       init->arg[1][1], init->arg[1][2], init->arg[1][3],
                       init->arg[1][4]);

            init = init->nxt;
        }

        fclose(out);
    }

    while(init != NULL){
        if(strcmp(init->arg[0], "00000") || strcmp(init->arg[1], "00000") ||
           init->wfill)
            printf("%0.3X %c%c %c%c%c %c%c %c%c%c\n", init->numlin,
                   init->arg[0][0], init->arg[0][1], init->arg[0][2],
                   init->arg[0][3], init->arg[0][4], init->arg[1][0],
                   init->arg[1][1], init->arg[1][2], init->arg[1][3],
                   init->arg[1][4]);

        init = init->nxt;
    }

}

argnode *searchElem(argnode *node, int numlin, char *arg, int type){

    if(type == 1){


        while(node->nxt != NULL && node->nxt->numlin != numlin)
            node = node->nxt;

        return node->nxt;
    }

    else if(type == 2){


        while(node->next[0] != NULL && strcmp(node->next[0]->label[0], arg))
            node = node->next[0];

        return node->next[0];
    }

    return NULL;
}

void insertElem(argnode *node, line *lin, int numlin, int type, argnode *dest){

    argnode *tmp;
    int cnt;

    if(type == 1){

        if(node->nxt == NULL){

            node->nxt = calloc(1, sizeof(argnode));
            node = node->nxt;
            node->type = 1;
            node->numlin = numlin;
        }

        else{

            while(node->nxt != NULL && node->nxt->numlin < numlin)
                node = node->nxt;

            tmp = node->nxt;
            node->nxt = calloc(1, sizeof(argnode));
            node = node->nxt;
            node->type = 1;
            node->nxt = tmp;
            node->numlin = numlin;
        }

        for(cnt = 0; cnt < 5; cnt++){

            node->arg[0][cnt] = '0';
            node->arg[1][cnt] = '0';
        }

        return;
    }

    else if(type == 2){

        if(node->next == NULL){

            node->next[0] = calloc(1, sizeof(argnode));
            node = node->next[0];
            node->type = 2;
            strcpy(node->label[0], lin->lbl);
            node->next[1] = dest;
        }

        else{

            while(node->next[0] != NULL && !strcmp(node->next[0]->label[0], lin->lbl))
                node = node->nxt;

            tmp = node->next[0];
            node->next[0] = calloc(1, sizeof(argnode));
            node = node->next[0];
            node->next[0] = tmp;
            node->type = 2;
            strcpy(node->label[0], lin->lbl);
            node->next[1] = dest;
        }
    }

    else if(type == 3){

        if(node->next == NULL){

            node->next[0] = calloc(1, sizeof(argnode));
            node = node->next[0];
            node->type = 3;
            strcpy(node->label[0], lin->sym);
            node->num = lin->num;
        }

        else{

            while(node->next[0] != NULL && !strcmp(node->next[0]->label[0], lin->sym))
                node = node->nxt;

            tmp = node->next[0];
            node->next[0] = calloc(1, sizeof(argnode));
            node = node->next[0];
            node->next[0] = tmp;
            node->type = 3;
            strcpy(node->label[0], lin->sym);
            node->num = lin->num;
        }
    }

    return ;

}
/*
void destroyLine(argnode *node, int type){

    if(node == NULL)
        return;

    else{
        destroyLine(node->next);
        free(node);
    }
}*/
 
    
