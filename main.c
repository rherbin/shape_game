#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./modules/ansi_escape.h"
#include"./modules/utils.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

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

void mainLoopSDL(void){
    
}

void mainloopASCII(void){
    int score = 0;
    int nscore = 0;
    char move;
    char r_id;
    char insert = 0;
    char side = 0;

    Forme ** ID = malloc(5*sizeof(Forme *));

    Forme ** next = malloc(5*sizeof(Forme *));

    for (int i = 0; i<5; i++){
        next[i] = getRandForme();
    }

    while (mainlist->length < 15){
        if (insert){
            for (int i = 0; i<4; i++){
                next[i] = next[i+1];
            }
            next[4] = getRandForme();
        }

        insert = 0;

        printf("\033[2J");
        printf("\033[0;0H");
        printf("Score : %d\n", score);
        printf("\n\n\n\n");
        printList(mainlist);
        printf("\n");
        //printList(blue);
        printf("\n\n\n\n");
        printf("=>\033[3%dm%c\x1b[0m<=     next : \x1b[0m", next[0]->col, next[0]->type);
        for (int i = 1; i<5; i++){
            printf("\033[3%dm%c ", next[i]->col, next[i] ->type);
        }
        printf("\x1b[0m\n");

        move = '\0';
        while(move != 'd' && move != 'g' && move != 'c' && move != 'f'){
            scanf(" %c", &move);
            getchar();
        }

        switch (move){
            case 'g':
                insert = 1;
                side = 0;
                break;
            case 'd':
                insert = 1;
                side = 1;
                break;
            case 'f':
                printf("Which shape to rotate ?\ns - Square | c - Circle | t - Triangle | d - Diamond\n");
                scanf(" %c", &r_id);
                switch (r_id){
                    case 's':
                        rotateList(squa, 1);
                        break;
                    case 'c':
                        rotateList(circ, 1);
                        break;
                    case 't':
                        rotateList(tri, 1);
                        break;
                    case 'd':
                        rotateList(los, 1);
                        break;
                    default:
                        break;
                }
                break;
            case 'c':
                printf("Which color to rotate ?\nr - Red | b - Blue | g - Green | y - Yellow\n");
                scanf(" %c", &r_id);
                switch (r_id){
                    case 'r':
                        rotateList(red, 0);
                        break;
                    case 'b':
                        printf("BLUE");
                        rotateList(blue, 0);
                        printf("BLUE");
                        break;
                    case 'g':
                        rotateList(green, 0);
                        break;
                    case 'y':
                        rotateList(yell, 0);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }

        if (insert){
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
        }

        nscore = 1;
        while (nscore != 0){
            nscore = checkListe(mainlist, ID);
            score += nscore;
            remAllListe(ID, nscore);
        }
    }

    printf("Game over !");

    for (int i = 0; i<5; i++){
        free(next[i]);
    }
    free(ID);
}

int main(int argc, char *argv[]) {

    mainlist = getList();
    circ = getList();
    squa = getList();
    los = getList();
    tri = getList();
    red = getList();
    blue = getList();
    yell = getList();
    green = getList();


    srand(time(NULL));
    setupConsole();
    mainloopASCII();
    restoreConsole();

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
}