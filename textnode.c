/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

typedef struct ArgNode{

    int numlin;
    char arg[2][5];
    char label[64];
    struct ArgNode *next;

} argnode;

argnode* newNode(int nl){

    argnode *nnode;
         
    nnode = calloc(1, sizeof(argnode));
    nnode->numlin = nl;
    nnode->next = NULL;

    return nnode;
}

void destroyLine(argnode *node){

    if(node == NULL)
        return;

    else{

        destroyLine(node->next);
        free(node);
    }
}
 
    
