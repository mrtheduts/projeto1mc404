/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

typedef struct ArgNode{

    int type;
    int right;

    int numlin;
    char label[65];


    union{

        char arg[2][6];
        unsigned long int num;
    };

    union{

        struct ArgNode *nxt;
        struct ArgNode *next[2];
    };

}argnode;

argnode *searchElem(argnode *node, int numlin, char *arg, int type){

    if(type == 1){


        while(node->nxt != NULL && node->nxt->numlin != numlin)
            node = node->nxt;

        return node->nxt;
    }

    else if(type == 2){


        while(node->next[0] != NULL && strcmp(node->next[0]->label, arg))
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
            node->type = 3;
            strcpy(node->label, lin->lbl);
            node->next[1] = dest;
        }

        else{

            while(node->next[0] != NULL && !strcmp(node->next[0]->label, lin->lbl))
                node = node->nxt;

            tmp = node->next[0];
            node->next[0] = calloc(1, sizeof(argnode));
            node = node->next[0];
            node->next[0] = tmp;
            node->type = 3;
            strcpy(node->label, lin->lbl);
            node->next[1] = dest;
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
 
    
