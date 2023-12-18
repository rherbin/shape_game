#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ansi_escape.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

typedef struct forme{
    char type; //R = ROND, C = CARRE, L = LOSANGE, T = TRIANGLE
    char col; //1 = ROUGE, 2 = BLEU, 3 = JAUNE, 4 = VERT
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

void printList(Liste * l){
    if (l->length == 0){
        return;
    }
    Maillon * m = l->first;
    for (int i = 0; i<l->length; i++){
        printf("\033[3%dm%c\x1b[0m ", m->f->col, m->f->type);
        m = m->next;
    }
}

void getForme(char type, char col, Forme * f){
    //Forme * f = malloc(sizeof(Forme));
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
    Maillon * m = malloc(sizeof(Maillon));
    m->f = f;
    if (l->length == 0){
        l->first = m;
        m->next = m;
        m->prev = m;
        l->length++;
        return;
    }
    m->next = l->first;
    m->prev = l->first->prev;
    l->first->prev->next = m;
    l->first->prev = m;
    if (pos == 0){
        l->first = m;
    }
    l->length++;
}

void remListe(Liste * l, Forme * rem){
    Maillon * m = l->first;
    if (m->f == rem){
        l->first->prev->next = l->first->next;
        l->first->next->prev = l->first->prev;
        l->first = l->first->next;
        free(m);
        l->length-=1;
        return;
    }
    m = m->next;
    for(int i = 0; i<l->length-1; i++){
        if (m->f == rem){
            m->prev->next = m->next;
            m->next->prev = m->prev;
            free(m);
            l->length -= 1;
            return;
        }
        m = m->next;
    }
}

int checkListe(Liste * l, Forme ** ID){

    int simC = 1;
    int simT = 1;
    char prevC = ' ';
    char prevT = ' ';
    Maillon * m = l->first;

    for (int i = 0; i < l->length; i++){

        if (m->f->col == prevC){
            simC++;
        } else if (simC>=3) {
            for (int j = 0; j<simC; j++){
                m = m->prev;
                ID[j] = m->f;
            }
            return simC;
        } else {
            simC = 1;
            prevC = m->f->col;
        }

        if (m->f->type == prevT){
            simT++;
            ID[simT-1] = m->f;
        } else if (simT>=3) {
            for (int j = 0; j<simT; j++){
                m = m->prev;
                ID[j] = m->f;
            }
            return simT;
        } else {
            simT = 1;
            prevT = m->f->type;
        }
        m = m->next;
    }
    if (simC>= 3 || simT>=3){
        for (int i = 0; i<max(simC, simT); i++){
            m = m->prev;
            ID[i] = m->f;
        }
        return max(simC,simT);
    }
    return 0;
}

void freeListe(Liste* l){
    Maillon * m = l->first->next;
    for (int i = 0; i < l->length-1; i++){
        m = m->next;
        free(m->prev->f);
        free(m->prev);
    }
    free(l->first->f);
    free(l->first);
}

void mainloopASCII(){
    int score = 0;
    int nscore = 0;
    char move;
    Forme ** ID = malloc(5*sizeof(Forme *));

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

        move = '0';
        while(move != 'd' && move != 'g'){
            scanf("%c", &move);
            getchar();
        }
        
        if (move == 'g'){
            appendListe(mainlist, current, 0);
        } else if (move == 'd'){
            appendListe(mainlist, current, 1);
        }
        nscore = checkListe(mainlist, ID);
        score += nscore;
        for (int i = 0; i<nscore; i++){ 
            remListe(mainlist, ID[i]);
        }
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