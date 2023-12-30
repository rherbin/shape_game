#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ansi_escape.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

// Liste * mainlist;
// Liste * circ;
// Liste * squa;
// Liste * los;
// Liste * tri;
// Liste * red;
// Liste * blue;
// Liste * yell;
// Liste * green;

int getVal(Forme * f){
    int val = 0;
    switch (f->type){
        case 'R':
            val += 0;
            break;
        case 'C':
            val += 1;
            break;
        case 'L':
            val += 2;
            break;
        case 'T':
            val += 3;
            break;
        default:
            break;
    }
    val += (f->col-1)*4;
    return val;
}

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

Forme * getRandForme(void){
    char types[] = "TRCL";
    int type = rand()%4;
    Forme * f = malloc(sizeof(Forme));

    getForme(types[type], rand()%4+1, f);
    return f;
}

Liste * getList(void){
    Liste * l = malloc(sizeof(Liste));
    l->length = 0;
    l->first = NULL;
    return l;
}

void appendListe(Liste * l, Forme * f, char pos){
    //Forme * f = malloc(sizeof(Forme));
    //getForme(f2->type, f2->col, f);
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
    if (l->length == 0){
        return;
    }
    Maillon * m = l->first;
    if (m->f == rem){
        if (l->length == 1){
            l->first = NULL;
            l->length -= 1;
            //free(m);
            return;
        }
        l->first->prev->next = l->first->next;
        l->first->next->prev = l->first->prev;
        l->first = l->first->next;
        //free(m);
        l->length-=1;
        return;
    }
    m = m->next;
    for(int i = 0; i<l->length-1; i++){
        if (m->f == rem){
            m->prev->next = m->next;
            m->next->prev = m->prev;
            //free(m);
            l->length -= 1;
            return;
        }
        m = m->next;
    }
}

void rotateList(Liste * l, char type){
    if (l->length <= 1){
        return;
    }

    Maillon * m = l->first;
    char tmp;
    if (type == 1){
        tmp = m->f->col;
    } else {
        tmp = m->f->type;
    }

    for (int i = 0; i<l->length-1; i++){
        if (type == 1){
            m->f->col = m->next->f->col;
        } else {
            m->f->type = m->next->f->type;
        }
        m = m->next;
    }

    if (type == 1){
        m->f->col = tmp;
    } else {
        m->f->type = tmp;
    }
}

int checkListe(Liste * l, Forme ** ID){

    int simC = 1;
    int simT = 1;
    char prevC = '\0';
    char prevT = '\0';
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