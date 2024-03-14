#pragma once
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2_gfx/SDL2_gfxPrimitives.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include <string.h>

typedef struct Piece{
    char shape; //R = ROND, C = CARRE, L = LOSANGE, T = TRIANGLE
    char col; //1 = ROUGE, 2 = VERT, 3 = JAUNE, 4 = BLEU
} Piece;

typedef struct maillon{
    struct maillon * next;
    struct maillon * prev;
    Piece * f;
    int mainID;
} Maillon;

typedef struct liste{
    int length;
    Maillon * first;
    char type; // 0 = col, 1 = shape
} Liste;

int getVal(Piece * f);
void printList(Liste * l);
void printState(Liste * mainlist, int score, Piece ** next);
Piece * getRandPiece(int n_shapes, int n_colors);
Liste * getList(void);
void appendListeID(Liste * l, Piece * f, int mainID);
void appendListe(Liste * l, Piece * f, char pos);
void remListe(Liste * l, Piece * rem);
void remMainListe(Liste * l, Piece * rem);
//void rotateMList(Liste * mainliste, MListe * l);
void rotateMList4(Liste * mainlist, Liste * rot, Liste ** collist, Liste ** shaplist, int n_col, int n_shap);
int checkListe(Liste * l, Piece ** ID);
void freeMainListe(Liste* l);
void freeListe(Liste* l);

void savegame(Liste * mainlist, Piece ** next, int score, int n_col, int n_shap, int max_piece);
void loadgame(Liste * mainlist, Piece ** next, int * score, int * n_col, int * n_shap, int * max_piece);

char * intToString(int n);
char * scoreString(int n);
char * shapeString(int n);
void colorFromNumber(int n, int * r, int * g, int * b);
void drawpoly(SDL_Renderer * rend, int sides, int x, int y, int size, int r, int g, int b);
void draw_edges_number(SDL_Renderer * rend, TTF_Font * font, int n, int x, int y);
void rota(double * x, double * y, double angle);
void aathickLineRGBA(SDL_Renderer * rend, int x1, int y1, int x2, int y2, int thickness, int r, int g, int b, int a);
int ButtonClick(SDL_Event * event, SDL_Rect * rect);
SDL_Texture * getTexFromImg(SDL_Renderer * rend, char * imgname);
void SDL_RenderDrawText(SDL_Renderer * rend, TTF_Font * font, int x, int y, char * text);

int loadscore(int score[10], char * initiales[4]);
int getScores(int scores[10], char * initiales[4]);