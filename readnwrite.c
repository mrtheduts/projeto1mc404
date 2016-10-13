/*
 *   Projeto 1 - Montador para a arquitetura do computador IAS
 *   Nome: Eduardo Moreira Freitas de Souza
 *   RA: 166779
 */

char *idArgs(char *arg, int *numlin) {

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
