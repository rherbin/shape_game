#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ansi_escape.h"

typedef struct forme{
    struct forme * next;
    struct forme * prev;
    char type; //R = ROND, C = CARRE, L = LOSANGE, T = TRIANGLE
    char col; //1 = ROUGE, 2 = BLEU, 3 = JAUNE, 4 = VERT
} Forme;

typedef struct list{
    int length;
    Forme * first;
} Liste;

void printList(Liste * l){
    if (l->length == 0){
        return;
    }
    Forme * f = l->first;
    for (int i = 0; i<l->length; i++){
        printf("\033[3%dm%c\x1b[0m ", f->col, f->type);
        f = f->next;
    }
}

void getForme(char type, char col, Forme * f){
    //Forme * f = malloc(sizeof(Forme));
    f->next = NULL;
    f->prev = NULL;
    f->col = col;
    f->type = type;
    //return f;
}

void getRandForme(Forme * f){
    char types[] = "TRCL";
    int type = rand()%4;

    getForme(types[type], rand()%4+1, f);
    //return f;
}

Liste * getList(void){
    Liste * l = malloc(sizeof(Liste));
    l->length = 0;
    l->first = NULL;
    return l;
}

void appendListe(Liste * l, Forme * f2, char pos){
    Forme * f = malloc(sizeof(Forme));
    getForme(f2->type, f2->col, f);
    if (l->length == 0){
        l->first = f;
        f->next = f;
        f->prev = f;
        l->length++;
        return;
    }
    f->next = l->first;
    f->prev = l->first->prev;
    l->first->prev->next = f;
    l->first->prev = f;
    if (pos == 0){
        l->first = f;
    }
    l->length++;
}

int checkListe(Liste * l, int * ID){
    int simC = 0;
    int simT = 0;
    char prevC = '0';
    char prevT = '0';
    Forme * f = l->first;

    for (*ID = 0; *ID < l->length; (*ID)++){
        if (simC == 3){
            f = f->next;
            (*ID)++;
            while(*ID < l->length-2 && f->col == prevC){
                (*ID)++;
                simC++;
                f = f->next;
            }
            return simC;
        }
        
        if (simT == 3){
            f = f->next;
            (*ID)++;
            while(*ID < l->length-2 && f->type == prevT){
                (*ID)++;
                simT++;
                f = f->next;
            }
            return simT;
        }

        if (f->col == prevC){
            simC++;
        } else {
            simC = 1;
            prevC = f->col;
        }

        if (f->type == prevT){
            simT++;
        } else {
            simT = 1;
            prevT = f->type;
        }

        f = f->next;
    }
    return 0;
}

void freeListe(Liste* l){
    Forme * f = l->first->next;
    for (int i = 0; i < l->length-1; i++){
        f = f->next;
        free(f->prev);
    }
    free(l->first);
}

void mainloopASCII(){
    int score = 0;
    int nscore = 0;
    char move;
    int * ID = malloc(sizeof(int));

    Liste * mainlist = getList();

    Liste * circ = getList();
    Liste * squa = getList();
    Liste * los = getList();
    Liste * tri = getList();

    Liste * red = getList();
    Liste * blue = getList();
    Liste * yell = getList();
    Liste * green = getList();

    Forme * current = malloc(sizeof(Forme));
    Forme * next = malloc(sizeof(Forme));

    getRandForme(next);

    while (mainlist->length < 15){
        *current = *next;
        getRandForme(next);

        printf("\033[2J");
        printf("\033[0;0H");
        printf("Score : %d\n", score);
        printf("\n\n\n\n");
        printList(mainlist);
        printf("\n\n\n\n");
        printf("=>\033[3%dm%c\x1b[0m<=     next : \033[3%dm%c\x1b[0m\n", current->col, current->type, next->col, next->type);

        scanf("%c", &move);
        getchar();

        if (move == 'g'){
            appendListe(mainlist, current, 0);
        } else if (move == 'd'){
            appendListe(mainlist, current, 1);
        }
        printf("Checklist");
        *ID = 1;
        printf("AfterID");
        nscore = checkListe(mainlist, ID);
        score += nscore;
    }

    freeListe(mainlist);

    free(mainlist);
    free(circ);
    free(squa);
    free(los);
    free(tri);
    free(red);
    free(blue);
    free(yell);
    free(green);

    free(current);
    free(next);

    free(ID);
}

int main(void) {
    srand(time(NULL));
    setupConsole();
    mainloopASCII();
    restoreConsole();
}