#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL2/include/SDL2/SDL.h"
#include "SDL2/include/SDL2/SDL_ttf.h"
#include "./modules/ansi_escape.h"
#include"./modules/utils.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)
#define FPS 60
#define WIDTH 1280
#define HEIGHT 720
#define n_color 4
#define n_shape 4

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

int mainLoopSDL(void){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() != 0){
        printf("Error initializing SDL_ttf: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window* wind = SDL_CreateWindow("Engine",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        WIDTH, HEIGHT, 0);
    if (!wind){
      printf("Error creating window: %s\n", SDL_GetError());
      SDL_Quit();
      return 0;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(wind, -1, render_flags);
    if (!rend){
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return 0;
    }
    
    char running = 1;
    SDL_Event event;

    SDL_Surface * txt_score;
    SDL_Texture * tex;
    SDL_Rect destr;
    destr.x = 17;
    destr.y = 10;
    TTF_Font * font = TTF_OpenFont("COMIC.TTF", 28);

    int score = 0;
    int nscore = 0;
    char * score_str;
    char insert = 0;
    char side;
    char update = 1;
    int d_col = 256*6/n_color;
    int r;
    int g;
    int b;

    SDL_Color white = {255, 255, 255};

    Forme ** ID = malloc(5*sizeof(Forme *));

    Forme ** next = malloc(5*sizeof(Forme *));

    for (int i = 0; i<5; i++){
        next[i] = getRandForme();
    }

    while (running){
        
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_LEFT:
                            insert = 1;
                            side = 0;
                            update = 1;
                            break;
                        case SDL_SCANCODE_RIGHT:
                            insert = 1;
                            side = 1;
                            update = 1;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        if (insert){
            appendListe(mainlist, next[0], (int)side);
            switch (next[0]->type){
                case 0:
                    appendListe(tri, next[0], (int)side);
                    break;
                case 1:
                    appendListe(circ, next[0], (int)side);
                    break;
                case 2:
                    appendListe(squa, next[0], (int)side);
                    break;
                case 3:
                    appendListe(los, next[0], (int)side);
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
            for (int i = 0; i<4; i++){
                next[i] = next[i+1];
            }
            next[4] = getRandForme();
        }

        nscore = 1;
        while (nscore != 0){
            nscore = checkListe(mainlist, ID);
            score += nscore;
            remAllListe(ID, nscore);
        }

        if (insert){
        }

        insert = 0;

        if (update){
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
            SDL_RenderClear(rend);

            SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
            score_str = scoreString(score);
            txt_score = TTF_RenderText_Solid(font, score_str, white);
            tex = SDL_CreateTextureFromSurface(rend, txt_score);
            destr.w = txt_score->w;
            destr.h = txt_score->h;

            SDL_RenderCopy(rend, tex, NULL, &destr);

            Maillon * m = mainlist->first;

            for(int i = 0; i<mainlist->length; i++){
                colorFromNumber((m->f->col-1)*d_col, &r, &g, &b);
                drawpoly(rend, m->f->type+3, (WIDTH-(mainlist->length)*60)/2+i*60+30, HEIGHT/2, 50, r, g, b);
                m = m->next;
            }

            for(int i = 0; i<5; i++){
                colorFromNumber((next[i]->col-1)*d_col, &r, &g, &b);
                drawpoly(rend, next[i]->type+3, (WIDTH-300)/2+i*60+30, HEIGHT-100, 50, r, g, b);
            }
            update = 0;
        }

        if (mainlist->length>=15){
            running = 0;
        }

        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);
    SDL_Quit();
    return 0;
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

    char * types = "TRCL";

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
        printf("\n\n\n\n");
        printf("=>\033[3%dm%c\x1b[0m<=     next : \x1b[0m", next[0]->col, types[next[0]->type]);
        for (int i = 1; i<5; i++){
            printf("\033[3%dm%c ", next[i]->col, types[next[i]->type]);
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
                case 0:
                    appendListe(tri, next[0], (int)side);
                    break;
                case 3:
                    appendListe(circ, next[0], (int)side);
                    break;
                case 2:
                    appendListe(squa, next[0], (int)side);
                    break;
                case 1:
                    appendListe(los, next[0], (int)side);
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
    free(next);

    free(ID);
}

int main(int argc, char *argv[]) {
    
    if (argc <= 1){
        printf("Please provide an argument");
        return 0;
    }

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

    if (!strcmp(argv[1], "ASCII")){
        setupConsole();
        mainloopASCII();
        restoreConsole();
    } else if (!strcmp(argv[1], "SDL")){
        mainLoopSDL();
    } else {
        printf("Unknown argument '%s'", argv[1]);
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

    return 0;
}