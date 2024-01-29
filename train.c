#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./modules/ansi_escape.h"
#include"./modules/utils.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

#define next_nbr 1
#define max_forme 10

Liste * mainlist;
Liste * circ;
Liste * squa;
Liste * los;
Liste * tri;
Liste * red;
Liste * blue;
Liste * yell;
Liste * green;

void remAllListe(Forme ** rem, int len){
    for (int i = 0; i<len; i++){
        remListe(mainlist, rem[i]);

        remListe(tri, rem[i]);
        remListe(squa, rem[i]);
        remListe(circ, rem[i]);
        remListe(los, rem[i]);

        remListe(red, rem[i]);
        remListe(blue, rem[i]);
        remListe(green, rem[i]);
        remListe(yell, rem[i]);
        free(rem[i]);
    }
}

// Forme * getValRev(int val){
//     Forme * f = malloc(sizeof(Forme));
//     switch (val%4){
//         case 0:
//             f->type = 'R';
//             break;
//         case 1:
//             f->type = 'C';
//             break;
//         case 2:
//             f->type = 'L';
//             break;
//         case 3:
//             f->type = 'T';
//             break;
//         default:
//             break;
//     }
//     f->col = val/4+1;
//     return f;
// }

Forme * getValRev(int val){
    char types[] = "RCLT";
    int type = val%4;
    Forme * f = malloc(sizeof(Forme));

    getForme(types[type], val/4+1, f);
    return f;
}

void ArrayTrain(Liste * l, int * state){
    if (l->length == 0){
        return;
    }
    Maillon * m = l->first;
    for (int i = 0; i<l->length; i++){
        state[i+7] = getVal(m->f);
        m = m->next;
    }
}

int * take_step(int state[22], int move){

    mainlist = getList();
    circ = getList();
    squa = getList();
    los = getList();
    tri = getList();
    red = getList();
    blue = getList();
    yell = getList();
    green = getList();

    int score = state[1];
    int nscore = 0;
    char insert = 0;
    char side = 0;

    int adj = 0;

    int * new_state = malloc((2+next_nbr+max_forme)*sizeof(int));

    Forme ** ID = malloc(5*sizeof(Forme *));

    Forme ** next = malloc(next_nbr*sizeof(Forme *));

    for (int i = 0; i<next_nbr; i++){
        next[i] = getValRev(state[i+2]);
    }

    for (int i = 0; state[i+next_nbr+2] != 16 && i<max_forme; i++){
        Forme * f = malloc(sizeof(Forme));
        f = getValRev(state[i+next_nbr+2]);
        appendListe(mainlist, f, 1);
        switch (f->type){
            case 'R':
                appendListe(circ, f, 1);
                break;
            case 'C':
                appendListe(squa, f, 1);
                break;
            case 'L':
                appendListe(los, f, 1);
                break;
            case 'T':
                appendListe(tri, f, 1);
                break;
            default:
                break;
        }
        switch (f->col){
            case 1:
                appendListe(red, f, 1);
                break;
            case 2:
                appendListe(green, f, 1);
                break;
            case 3:
                appendListe(yell, f, 1);
                break;
            case 4:
                appendListe(blue, f, 1);
                break;
            default:
                break;
        }
    }
    //printList(mainlist);
    //printf("\n");

    /* */

    switch (move){
        case 0:
            insert = 1;
            side = 0;
            break;
        case 1:
            insert = 1;
            side = 1;
            break;
        case 2:
            rotateList(squa, 1);
            break;
        case 3:
            rotateList(circ, 1);
            break;
        case 4:
            rotateList(tri, 1);
            break;
        case 5:
            rotateList(los, 1);
            break;
        case 6:
            rotateList(red, 0);
            break;
        case 7:
            rotateList(blue, 0);
            break;
        case 8:
            rotateList(green, 0);
            break;
        case 9:
            rotateList(yell, 0);
            break;
        default:
            break;
    }

    if (insert){
        if (side == 0 && (mainlist->first->f->col == next[0]->col || mainlist->first->f->type == next[0]->type)){
            adj = 1;
        }
        if (side == 1 && (mainlist->first->prev->f->col == next[0]->col || mainlist->first->prev->f->type == next[0]->type)){
            adj = 1;
        }
        appendListe(mainlist, next[0], (int)side);
        switch (next[0]->type){
            case 'R':
                appendListe(circ, next[0], (int)side);
                break;
            case 'C':
                appendListe(squa, next[0], (int)side);
                break;
            case 'L':
                appendListe(los, next[0], (int)side);
                break;
            case 'T':
                appendListe(tri, next[0], (int)side);
                break;
            default:
                break;
        }

        switch (next[0]->col){
            case 1:
                appendListe(red, next[0], (int)side);
                break;
            case 2:
                appendListe(green, next[0], (int)side);
                break;
            case 3:
                appendListe(yell, next[0], (int)side);
                break;
            case 4:
                appendListe(blue, next[0], (int)side);
                break;
            default:
                break;
        }
        for (int i = 0; i<next_nbr-1; i++){
            next[i] = next[i+1];
        }
        next[next_nbr-1] = getRandForme(4, 4);

        nscore = 1;
        while (nscore != 0){
            nscore = checkListe(mainlist, ID);
            score += nscore;
            remAllListe(ID, nscore);
        }
    }

    if (mainlist->length >= max_forme){
        new_state[0] = 1;
    } else {
        new_state[0] = 0;
    }

    if (score >= 3){
        new_state[1] = score;
    } else {
        new_state[1] = adj;
    }

    for (int i = 0; i<next_nbr; i++){
        new_state[i+2] = getVal(next[i]);
    }
    ArrayTrain(mainlist, new_state);
    for(int i = mainlist->length+next_nbr+2; i<next_nbr+max_forme+2; i++){
        new_state[i] = 16;
    }

    //printList(mainlist);

    return new_state;
}

// int main(){
//     setupConsole();
//     srand(time(NULL));
//     int array[] = {0, 0, 12, 13, 5, 6, 4, 4, 12, 14, 2, 7, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};
//     int * new = take_step(array, 1);
//     for (int i = 0; i<22; i++){
//         printf("%d ", new[i]);
//     }

//     int v = 12;
//     printf("\n%d", getVal(getValRev(v)));
//     restoreConsole();
//     return 0;
// }