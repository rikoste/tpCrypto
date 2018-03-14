#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "error.h"

/*
    Cette fonction alloue la mèmoire et copie l'intégralité du fichier dans une chaine de caracère
*/
int open_file(char *path,char *str) {
    int ret = -1;
    fpos_t debut_fichier;
    str = NULL;
    int longueur = 0;
    char ch_tmp;
    int continuer = 0;
    FILE *f = fopen(
        path,
        "r"
    );
    if(f == NULL) {
        //error file
        return ERROR_FILE;
    }
    

    ret = fgetpos(
        f,
        &debut_fichier
    );
    if(ret != 0) {
        return ERROR_FILE;
    }

    do {
        ch_tmp = fgetc(f);
        if(ch_tmp == EOF) {
            continuer = 1;
        } else {
            if(ch_tmp >= 'A' && ch_tmp <= 'Z') {
                longueur++;
            }
        }
    }while(continuer == 0);

    ret = fsetpos(
        f,
        &debut_fichier
    );
    if(ret != 0) {
        return ERROR_FILE;
    }

    str = malloc(sizeof(char) * (longueur + 1));
    if(str == NULL) {
        return ERROR_ALLOCATION;
    }
    memset(
        str,
        '\0',
        longueur + 1
    );
    longueur = 0;
    do {
        ch_tmp = fgetc(f);
        if(ch_tmp == EOF) {
            continuer = 1;
        } else {
            if(ch_tmp >= 'A' && ch_tmp <= 'Z') {
                str[longueur] = ch_tmp;
                longueur++;
            }
        }
    }while(continuer == 0);

    ret = fclose(f);
    if(ret != 0) {
        //error file
        if(str != NULL) {
            free(str);
            str = NULL;
        }
        return ERROR_FILE;
    }
    return OK;
}

int write_file(char *path, char *str) {
    int i = 0;
    int ret = -1;
    char cret = 'A';
    if(path == NULL || str == NULL) {
        return ERROR_INVALID_ARGUMENT;
    }
    FILE *f = fopen(
        path,
        "w"
    );
    if(f == NULL) {
        return ERROR_FILE;
    }

    while(path[i] != '\0') {
        cret = fputc(
            path[i],
            f
        );
        if(cret == 'EOF') {
            fclose(f);
            return ERROR_FILE;
        }
    }
    ret = fclose(f);
    if(ret != 0) {
        return ERROR_FILE;
    }
    return OK;
    
}