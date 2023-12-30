#pragma once

typedef struct forme{
    char type; //R = ROND, C = CARRE, L = LOSANGE, T = TRIANGLE
    char col; //1 = ROUGE, 2 = VERT, 3 = JAUNE, 4 = BLEU
} Forme;

typedef struct maillon{
    struct maillon * next;
    struct maillon * prev;
    Forme * f;
} Maillon;

typedef struct list{
    int length;
    Maillon * first;
} Liste;

int getVal(Forme * f);
void printList(Liste * l);
void getForme(char type, char col, Forme * f);
Forme * getRandForme(void);
Liste * getList(void);
void appendListe(Liste * l, Forme * f, char pos);
void remListe(Liste * l, Forme * rem);
void rotateList(Liste * l, char type);
int checkListe(Liste * l, Forme ** ID);
void freeListe(Liste* l);