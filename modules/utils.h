#pragma once
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2_gfx/SDL2_gfxPrimitives.h"

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

char * intToString(int n);
char * scoreString(int n);
void colorFromNumber(int n, int * r, int * g, int * b);
void drawpoly(SDL_Renderer * rend, int sides, int x, int y, int size, int r, int g, int b);
void rota(double * x, double * y, double angle);
void aathickLineRGBA(SDL_Renderer * rend, int x1, int y1, int x2, int y2, int thickness, int r, int g, int b, int a);