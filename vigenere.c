#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vigenere.h"
#include "error.h"
/**
    Fonction decale char.
    Cette fonction effectue un decalage sur une lettre.
    Elle retourne 0 si aucun soucis, sinon elle renvoie un maessage d'erreur.
    Retourne ERROR_LETTRE si la lettre en entrée n'est pas valide
*/
int decalage_char(
    char src,
    char *dest,
    int decalage
) {

    //-------------------------------------------------------------------------
    //
    // Verification de la lettre en entrée
    //
    //-------------------------------------------------------------------------

    if(
        ( 'A' > src ) ||
        ( 'Z' < src )
    ) {
        return ERROR_LETTRE;
    }

    //-------------------------------------------------------------------------
    //
    // Modification du code pour qu'il soit valide (entre 0 et 25).
    //
    //-------------------------------------------------------------------------

    // On s'assure que le décalage est positif
    // en lui rajoutant 26 autant de fois que nécessaire.
    while( decalage < 0 ) {
        decalage = decalage + 26;
    }

    decalage = decalage % 26;

    //-------------------------------------------------------------------------
    //
    // Chiffrement de la lettre
    //
    //-------------------------------------------------------------------------

    (*dest) = (
        (
            ( 
                src +
                decalage -
                'A' 
            ) % 
            26
        ) +
        'A'
    );

    return OK;
}


/**
    Fonction vigenere_chiffrement.
    Cette fonction chiffre le message chaine et l'ecrit dans dest.
    Elle peut retourner ERROR_CHAINE_VIDE si le message en entrée est null ou que la clé est incvalide.
    Elle retourne OK si il n'y a aucun probleme.
*/ 
int vigenere_chiffrement(
    char *chaine,
    char *dest,
    int longueur,
    char *code,
    int longueur_code
) {
    if( chaine == NULL ) {
        return ERROR_CHAINE_VIDE;
    }
    if( code == NULL ) {
        return ERROR_CHAINE_VIDE;
    }
    if( dest == NULL ) {
        return ERROR_CHAINE_VIDE;
    }
    int i = 0;
    int j = 0;
    int ret = ERROR;
    while( i < longueur ) {
        if(j == longueur_code) {
            j = 0;
        }
        if(
            chaine[i] == '\0'
        ) {
            dest[i] = '\0';
            break;
        }
        ret = decalage_char(
            chaine[i],
            &dest[i],
            code[j]
        );
        if(ret == ERROR_LETTRE) {
            dest[i] = chaine[i];
        }
        j++;
        i++;
    }
    if( i == longueur) {
        dest[ i - 1] = '\0';
    }
    return OK;
}

/**
    Fonction vigenere_dechiffrement.
    Cette fonction dechiffre le message chaine et l'ecrit dans dest.
    Elle peut retourner ERROR_CHAINE_VIDE si le message en entrée est null ou que la clé est invalide.
    Elle retourne OK si il n'y a aucun probleme.
*/ 
int vigenere_dechiffrement(
    char *chaine,
    char *dest,
    int longueur,
    char *code,
    int longueur_code
) {
    if( chaine == NULL ) {
        return ERROR_CHAINE_VIDE;
    }
    if( code == NULL ) {
        return ERROR_CHAINE_VIDE;
    }
    if( dest == NULL ) {
        return ERROR_CHAINE_VIDE;
    }
    int i = 0;
    int j = 0;
    int ret = ERROR;
    while( i < longueur ) {
        if(j == longueur_code) {
            j = 0;
        }
        if(
            chaine[i] == '\0'
        ) {
            dest[i] = '\0';
            break;
        }
        ret = decalage_char(
            chaine[i],
            &dest[i],
            0 - code[j]
        );
        if(ret == ERROR_LETTRE) {
            dest[i] = chaine[i];
        }
        j++;
        i++;
    }
    if( i == longueur) {
        dest[ i - 1] = '\0';
    }
    return OK;
}