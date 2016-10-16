/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

#define SIZEHEXA 13

typedef struct Line{

    int dir;
    int label;
    int symbol;
    int inst;
    int line;
    unsigned long int num;
    int negative;
    int hex;
    char lbl[65];
    char sym[65];
    unsigned long int numwfill;
    int negativewfill;

}line;

void printLine(line *strct){

    printf("====================\n");
    printf("DIR %d\n", strct->dir);
    printf("LABEL %d\n", strct->label);
    printf("SYMBOL %d\n", strct->symbol);
    printf("INSTRUCTION %d\n", strct->inst);
    printf("NUMBER %ld\n", strct->num);
    printf("NEGATIVE %d\n", strct->negative);
    printf("IS HEX %d\n", strct->hex);
    printf("LABEL %s\n", strct->lbl);
    printf("SYMBOL %s\n", strct->sym);
    printf("NUM WFILL %d\n", strct->numwfill);
    printf("NEGATIVE WFILL %d\n", strct->negativewfill);
    printf("====================\n");
}

int issym(char *arg, line *strct, int islbl){

    int cntstr = 0, quomarks = 0;
    char tmp;

    if(isdigit(arg[0]))
        return 0;

    if(arg[0] == '\"' && islbl == 2){

        quomarks = 1;
        arg++;
    }


    while(isalnum(arg[cntstr]) || arg[cntstr] == '_') {
        cntstr++;
    }

    if(quomarks){

        tmp = arg[cntstr];
        arg[cntstr] = 0;
        memcpy(strct->sym, arg, cntstr);
        //printf("%s\n", arg);
        strct->symbol = 1;
        return 1;

    }

    else if((!arg[cntstr] || isspace(arg[cntstr])) && !islbl){

        memcpy(strct->sym, arg, cntstr);
        strct->symbol = 1;
        return 1;
    }

    else if(islbl && arg[cntstr] == ':' && (!arg[cntstr + 1] || isspace(arg[cntstr + 1]))){

        memcpy(strct->lbl, arg, cntstr + 1);
        strct->label = 1;
        return 1;
    }

    else
        return 0;

}

int numPlaces (int n){
    if(n < 0)
        return 1 + numPlaces(n*-1);
    if(n < 10)
        return 1;
    return 1 + numPlaces (n / 10);
}

int isHexNum(char *arg, line *strct, int quomarks){

    char *temp, c;

    if(quomarks)
        arg++;


    if(!strncmp(arg, "0x", 2)) {


        if(quomarks) {

            c = arg[12];
            arg[12] = 0;
        }

        if (isxdigit(arg[0])) {

            strct->num = strtol(arg, &temp, 16);
            strct->hex = 1;

            if(quomarks)
                arg[12] = c;

            return 1;
        }

        if(quomarks)
            arg[12] = c;
    }

    else
        return 0;
}

int isDeciNum(char *arg, line *strct, int quomarks){

    int cntdeci = 0;
    char *temp;

    if(quomarks)
        arg++;

    if(arg[0] == '-') {

        strct->negative = 1;
        arg++;
    }



    while(isdigit(arg[cntdeci]))
        cntdeci++;

    if(cntdeci == 0)
        return 0;

    if(quomarks)
        arg[cntdeci] = ' ';

    //printf("%s\n",arg);

    if(cntdeci && (isspace(arg[cntdeci]) || !arg[cntdeci])){

        strct->num = strtol(arg, &temp, 10);
        //printf("Strct num %d/%.10X\n", strct->num, strct->num);
        return 1;
    }

    else
        return 0;
}

int idDir(char *arg, int cntdb, line *strct){

    unsigned long int tmp;
    int cntstr, cnthex = 0, cntdeci = 0, tmpnegative;
    char *temp;

    if(cntdb == 1){

        if(issym(arg + 5, strct, 0)){


            if(isHexNum(arg + strlen(strct->sym) + 6, strct, 0) || isDeciNum(arg + strlen(strct->sym) + 6, strct, 0)){

                strct->dir = 1;

                if(strct->hex)
                    return 6 + strlen(strct->sym) + SIZEHEXA;

                else
                    return 6 + strlen(strct->sym) + numPlaces(strct->num);
            }
        }

        else {

            strct->dir = -1;
            return 0;
        }

    }

    else if(cntdb == 2){

        if(isHexNum(arg + 5, strct, 0) || isDeciNum(arg + 5, strct, 0)){

            strct->dir = 2;

            if(strct->hex)
                return 6 + SIZEHEXA;
            else
                return 6 + numPlaces(strct->num);
        }

        else {

            strct->dir = -2;
            return 0;
        }

    }

    else if(cntdb == 3){

        if(isDeciNum(arg + 7, strct, 0)){

            strct->dir = 3;
            return 7 + numPlaces(strct->num);
        }

        else{

            strct->dir = -3;
            return 0;
        }
    }

    else if(cntdb == 4){

        if(isDeciNum(arg + 7, strct, 0)){

            if(strct->negative) {

                strct->dir = 4;
                return 0;
            }

            else{

                tmp = strct->num;
                tmpnegative = strct->negative;

                if(isDeciNum(arg + 8 +numPlaces(strct->num), strct, 0) ||
                        isHexNum(arg + 8 + numPlaces(strct->num), strct, 0) ||
                        issym(arg + 8 + numPlaces(strct->num), strct, 0)){


                    if(!strct->symbol) {

                        strct->numwfill = strct->num;
                        strct->negativewfill = strct->negative;
                        strct->num = tmp;
                        strct->negative = tmpnegative;
                    }

                    strct->dir = 4;

                    if(strct->hex)
                        return 9 + numPlaces(strct->num) + SIZEHEXA;

                    else if(strct->symbol)
                        return 8 + numPlaces(strct->num) + strlen(strct->sym);

                    else if(strct->negativewfill)
                        return 9 + numPlaces(strct->num) + numPlaces(strct->numwfill);

                    else
                        return 8 + numPlaces(strct->num) + numPlaces(strct->numwfill);



                }
            }
        }

        strct->dir = -4;
        return 0;
    }

    else if(cntdb == 5){

        if(isHexNum(arg + 6, strct, 0) || isDeciNum(arg + 6, strct, 0) || issym(arg + 6, strct, 0)){

            strct->dir = 5;

            if(strct->negative)
                return 0;

            else if(strct->hex)
                return 6 + SIZEHEXA;

            else if(strct->symbol)
                return 6 + strlen(strct->sym);

            else
                return 6 + numPlaces(strct->num);


        }
    }
}

line *idArgs(char *arg, int *numlin, int numlinin, FILE *out) {

    char ddb[][8] = {"blank", ".set ", ".org ", ".align ", ".wfill ", ".word "};
    char idb[][9] = {"blank", "LD ", "LD- ", "LD| ", "LDmq ", "LDmq_mx ", "ST ", "JMP ", "JUMP+ ",
    "ADD ", "ADD| ", "SUB ", "SUB| ", "MUL ", "DIV ", "LSH ", "RSH ", "STaddr "};
    int cntdb = 0;
    line *strct;
    int controle = 0;

    strct = calloc(1, sizeof(line));

    while(arg[0]){

        //printf("|%s|\n",arg);

        controle++;

        if(controle > 10)
            return NULL;

        if (arg[0] == '.') {

            if(strct->dir){

                if(out == NULL)
                    printf("ERROR on line %d\nDuas diretivas em uma unica linha.\n", numlinin);
                else
                    fprintf(out, "ERROR on line %d\nDuas diretivas em uma unica linha.\n", numlinin);

                free(strct);
                return NULL;
            }


            for (cntdb = 1; cntdb <= 5; cntdb++)
                if (!strncmp(arg, ddb[cntdb], strlen(ddb[cntdb])))
                    break;

            if (cntdb == 6) {

                if(out == NULL)
                    printf("ERROR on line %d\nDiretiva inexistente.\n", numlinin);
                else
                    fprintf(out, "ERROR on line %d\nDiretiva inexistente.\n", numlinin);

                free(strct);
                return NULL;
            }

            else if(strct->inst){

                if(out == NULL)
                    printf("ERROR on line %d\nDiretiva com instrucao.\n", numlinin);
                else
                    fprintf(out, "ERROR on line %d\nDiretiva com instrucao.\n", numlinin);

                free(strct);
                return NULL;
            }

            else
                arg += idDir(arg, cntdb, strct);

            if((strct->dir == 1 || strct->dir == 2 || strct->dir == 3 || strct->dir == 4) &&
                    (strct->num > 1023 || strct->negative)){

                if(out == NULL)
                    printf("ERROR on line %d\nNumero não compativel.\n", numlinin);
                else
                    fprintf(out, "ERROR on line %d\nNumero não compativel.\n", numlinin);

                free(strct);
                return NULL;
            }

            else if((strct->dir == 3 || strct->dir == 4) && !strct->num){

                if(out == NULL)
                    printf("ERROR on line %d\nZero não é valido.\n", numlinin);
                else
                    fprintf(out, "ERROR on line %d\nZero não é valido.\n", numlinin);

                free(strct);
                return NULL;
            }

            else if(strct->dir == -1){

                if(out == NULL)
                    printf("ERROR on line %d\nSYM não compativel com diretiva .set.\n",numlinin);
                else
                    fprintf(out, "ERROR on line %d\nSYM não compativel com diretiva .set.\n",numlinin);

                free(strct);
                return NULL;
            }

            else if(strct->dir == -3){

                if(out == NULL)
                    printf("ERROR on line %d\nArgumento não compativel com diretiva .align.\n", numlinin);
                else
                    fprintf(out, "ERROR on line %d\nArgumento não compativel com diretiva .align.\n", numlinin);

                free(strct);
                return NULL;
            }

            else if(strct->dir == -4){

                if(out == NULL)
                    printf("ERROR on line %d\nArgumento não compativel com diretiva .wfill.\n", numlinin);
                else
                    fprintf(out, "ERROR on line %d\nArgumento não compativel com diretiva .wfill.\n", numlinin);

                free(strct);
                return NULL;
            }

            else if((strct->num + *numlin > 1023) && strct->dir == 4){

                if(out == NULL)
                    printf("ERROR on line %d\nNumero de linhas para preencher ultrapassa o limite da memoria.\n", numlinin);
                else
                    fprintf(out, "ERROR on line %d\nNumero de linhas para preencher ultrapassa o limite da memoria.\n", numlinin);

                free(strct);
                return NULL;
            }

            else if(strct->dir == 5 && strct->negative){

                if(out == NULL)
                    printf("ERROR on line %d\nNumero não compativel com diretiva.\n", numlinin);
                else
                    fprintf(out, "ERROR on line %d\nNumero não compativel com diretiva.\n", numlinin);

                free(strct);
                return NULL;
            }
        }

        else{

            if (!isdigit(arg[0])) {

                if(!strct->label) {

                    if (issym(arg, strct, 1)){

                        if (strct->dir || strct->inst){

                            if(out == NULL)
                                printf("ERROR on line %d\nDefinicao de rotulo depois de diretiva/instrucao\n", numlinin);
                            else
                                fprintf(out, "ERROR on line %d\nDefinicao de rotulo depois de diretiva/instrucao\n", numlinin);

                            free(strct);
                            return NULL;
                        }

                        arg += strlen(strct->lbl) + 1;
                        continue;
                    }
                }

                if(!strct->inst){

                    for (cntdb = 1; cntdb <= 17; cntdb++) {

                        //printf("|%s||%s|\n", arg, idb[cntdb]);
                        //printf("|%d|\n",strncmp(arg, idb[cntdb], strlen(idb[cntdb])));

                        if((cntdb == 15 || cntdb == 16) && (arg[strlen(idb[cntdb]) - 1] == 0 ||
                                arg[strlen(idb[cntdb]) - 1] == '\n') && !strncmp(arg, idb[cntdb], strlen(idb[cntdb]) - 2)) {
                            break;
                        }

                        if (!strncmp(arg, idb[cntdb], strlen(idb[cntdb])))
                            break;
                    }


                    if(cntdb == 18){

                        if(out == NULL)
                            printf("ERROR on line %d\nInstrucao invalida\n", numlinin);
                        else
                            fprintf(out, "ERROR on line %d\nInstrucao invalida\n", numlinin);

                        free(strct);
                        return NULL;
                    }

                    else if(strct->dir){

                        if(out == NULL)
                            printf("ERROR on line %d\nDiretiva com instrucao.\n", numlinin);
                        else
                            fprintf(out, "ERROR on line %d\nDiretiva com instrucao.\n", numlinin);

                        free(strct);
                        return NULL;
                    }

                    else{

                        if(cntdb == 1)
                            strct->inst = 1;

                        else if(cntdb == 2)
                            strct->inst = 2;

                        else if(cntdb == 3)
                            strct->inst = 3;

                        else if(cntdb == 4)
                            strct->inst = 10;

                        else if(cntdb == 5)
                            strct->inst = 9;

                        else if(cntdb == 6)
                            strct->inst = 33;

                        else if(cntdb == 7)
                            strct->inst = 13;

                        else if(cntdb == 8)
                            strct->inst = 15;

                        else if(cntdb == 9)
                            strct->inst = 5;

                        else if(cntdb == 10)
                            strct->inst = 7;

                        else if(cntdb == 11)
                            strct->inst = 6;

                        else if(cntdb == 12)
                            strct->inst = 8;

                        else if(cntdb == 13)
                            strct->inst = 11;

                        else if(cntdb == 14)
                            strct->inst = 12;

                        else if(cntdb == 15)
                            strct->inst = 20;

                        else if(cntdb == 16)
                            strct->inst = 21;

                        else if(cntdb == 17)
                            strct->inst = 18;

                        arg += strlen(idb[cntdb]);

                        if(cntdb == 15 || cntdb == 16)
                            continue;

                        if(isHexNum(arg, strct, 1) ||isDeciNum(arg, strct, 1)) {

                            if(strct->negative) {

                                if(out == NULL)
                                    printf("ERROR on line %d\nNumero negativo na instrucao.\n", numlinin);
                                else
                                    fprintf(out, "ERROR on line %d\nNumero negativo na instrucao.\n", numlinin);

                                free(strct);
                                return NULL;
                            }

                            else if(strct->hex)
                                arg += SIZEHEXA + 2;
                            else
                                arg += numPlaces(strct->num) + 2;

                            continue;
                        }

                        else if(issym(arg, strct, 2)){

                            if(strct->symbol)
                                arg += strlen(strct->sym) + 2;

                            continue;

                        }
                    }

                }

                else{

                    if(out == NULL)
                        printf("ERROR on line %d\nNumero maximo de palavras excedido.\n", numlinin);
                    else
                        fprintf(out, "ERROR on line %d\nNumero maximo de palavras excedido.\n", numlinin);

                    free(strct);
                    return NULL;

                }
            }

            if(out == NULL)
                printf("ERROR on line %d\nInstrucao/rotulo invalido", numlinin);
            else
                fprintf(out, "ERROR on line %d\nInstrucao/rotulo invalido", numlinin);

            free(strct);
            return NULL;
        }
    }

    return strct;
}

int getLine(char *templine, FILE *in){

    int tmp, cntChar = 0;
    char line = 0;

    tmp = fgetc(in);

    if(tmp == '\t')
        tmp = ' ';

    while(tmp != '#' && tmp != '\n' && tmp != EOF){

        if(!line && (tmp == ' ' || tmp == '\t')){}

        else if(!(cntChar && (tmp == ' ' && templine[cntChar - 1] == ' '))) {

            line = 1;
            templine[cntChar] = tmp;
            cntChar++;

            if(cntChar == 85);
        }

        tmp = fgetc(in);

        if(tmp == '\t')
            tmp = ' ';
    }

    if(tmp == '#')
        do{
            tmp = fgetc(in);
        }while(tmp != '\n' && tmp != EOF);

    if(templine[cntChar - 1] == ' ')
        templine[cntChar - 1] = 0;
    else
        templine[cntChar] = 0;

    //printf("%s\n", templine);

    if(tmp == EOF && !line)
        return 0;

    else if(tmp == EOF && line)
        return 2;

    else if(line)
        return 1;

    else
        return -1;

}
