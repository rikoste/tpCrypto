
#define ERREUR -1
#define OK 0
#define ERREUR_LETTRE -2
#define ERREUR_CHAINE_VIDE -3

int decalage_char(char src,char *dest,int decalage);
int vigenere_chiffrement(char *chaine,char *dest,int longueur,char *code,int longueur_code);
int vigenere_dechiffrement(char *chaine,char *dest,int longueur,char *code,int longueur_code);