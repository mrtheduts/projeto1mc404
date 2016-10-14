/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

typedef struct Line{

    int dir;
    int label;
    int islblfirst;
    int instr;
    unsigned long int num;
    int negative;
    int hex;
    char lbl[65];
    unsigned long int numwfill;
    int negativewfill;

}line;

//int issym(char *arg, )

int numPlaces (int n) {
    if(n < 0)
        return 1 + numPlaces(n*-1);
    if(n < 10)
        return 1;
    return 1 + numPlaces (n / 10);
}

int isHexNum(char *arg, line *strct){

    char *temp, c;

    if(!strncmp(arg, "\"0x", 3)) {

        c = arg[13];
        arg[13] = 0;
        arg ++;

        if (isxdigit(arg[0])) {

            strct->num = strtol(arg, &temp, 16);
            strct->hex = 1;
            printf("Strct num %ld/%.10lX\n", strct->num, strct->num);
            arg[13] = c;
            return 1;
        }
    }

    else
        return 0;
}

int isDeciNum(char *arg, line *strct){

    int cntdeci = 0;
    char *temp;

    if(arg[0] == '-') {

        strct->negative = 1;
        arg++;
    }

    while(isdigit(arg[cntdeci]))
        cntdeci++;
    
    if(cntdeci && (isspace(arg[cntdeci]) || !arg[cntdeci])){

        strct->num = strtol(arg, &temp, 10);
        printf("Strct num %d/%.10X\n", strct->num, strct->num);
        return 1;
    }

    else
        return 0;
}

int idDir(char *arg, int cntdb, int *numlin, char *right, line *strct){

    int cntstr, cnthex = 0, cntdeci = 0;
    char *temp;

    if(cntdb == 1){

    }

    else if(cntdb == 2){

        if(isHexNum(arg + 5, strct) || isDeciNum(arg + 5, strct)){

            strct->dir = 2;

            if(strct->hex)
                return 20;
            else
                return 6+numPlaces(strct->num);
        }

    }

    else if(cntdb == 3){

        if(isDeciNum(arg + 7, strct)){

            if(strct->negative){

                strct->dir = -3;
                return 0;
            }

            strct->dir = 3;
            return 6+numPlaces(strct->num);
        }

        else{

            strct->dir = -3;
            return 0;
        }
    }

    else if(cntdb == 5){

        if(isHexNum(arg + 6, strct) || isDeciNum(arg + 6, strct)){

            strct->dir = 5;
        }
    }
}

line *idArgs(char *arg, int *numlin, char *right, int numlinin) {

    char ddb[][8] = {"blank", ".set ", ".org ", ".align ", ".wfill ", ".word "};
    int cntdb = 0;
    line *strct;

    strct = calloc(1, sizeof(line));

    while(arg){

        if (arg[0] == '.') {

            if(strct->dir){

                printf("Error on line %d\nDuas diretivas em uma unica linha.\n", numlinin);
                return NULL;
            }


            for (cntdb = 1; cntdb <= 5; cntdb++)
                if (!strncmp(arg, ddb[cntdb], strlen(ddb[cntdb])))
                    break;

            if (cntdb == 6) {

                printf("Error on line %d\nDiretiva inexistente.\n", numlinin);;
                return NULL;
            }

            else
                arg += idDir(arg, cntdb, numlin, right, strct);

            if((strct->dir == 2 || strct->dir == 3) && (strct->num > 1023 || strct->negative)){

                printf("Error on line %d\nNumero fora do mapa de memoria.\n", numlinin);
                return NULL;
            }

            if(strct->dir == -3){

                printf("Error on line %d\nArgumento não compativel com diretiva .align.\n", numlinin);
                return NULL;
            }


            printf("%s\n", arg);
            system("sleep 5s");
        }
    }

    return NULL;
}

int getLine(char *templine, FILE *in){

    int tmp, cntChar = 0;
    char line = 0;

    tmp = fgetc(in);

    while(tmp != '#' && tmp != '\n' && tmp != EOF){

        if(!line && (tmp == ' ' || tmp == '\t')){}

        else if(!(cntChar && (tmp == ' ' && templine[cntChar - 1] == ' ' ||
             (tmp == '\t' && templine[cntChar - 1] == '\t')))) {

            line = 1;
            templine[cntChar] = tmp;
            cntChar++;
        }

        tmp = fgetc(in);
    }

    if(tmp == '#')
        do{
            tmp = fgetc(in);
        }while(tmp != '\n' && tmp != EOF);

    if(templine[cntChar - 1] == ' ')
        templine[cntChar - 1] = 0;
    else
        templine[cntChar] = 0;

    printf("%s\n", templine);

    if(tmp == EOF && !line)
        return 0;

    else if(tmp == EOF && line)
        return 2;

    else if(line)
        return 1;

    else
        return -1;

}
