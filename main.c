#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL2/include/SDL2/SDL.h"
#include "SDL2/include/SDL2/SDL_ttf.h"
#include "./SDL2/include/SDL2/SDL_image.h"
#include "./modules/ansi_escape.h"
#include"./modules/utils.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)
#define FPS 60
#define WIDTH 1280
#define HEIGHT 720

SDL_Color white = {255, 255, 255};

void remAllListe(Forme ** rem, Liste * mainlist, Liste ** colList, Liste ** shapList, int len, int n_col, int n_shap){
    for (int i = 0; i<len; i++){
        remListe(mainlist, rem[i]);

        remListe(colList[(int)rem[i]->col], rem[i]);

        remListe(shapList[(int)rem[i]->type], rem[i]);

        free(rem[i]);
    }
}

int mainLoopSDL(SDL_Renderer * rend, int n_col, int n_shap, int max_shapes){

    // Liste ** colList = malloc(sizeof(Liste *) * n_col);
    // Liste ** shapList = malloc(sizeof(Liste *) * n_shap);

    // Liste * mainlist = getList();

    // for (int i = 0; i< n_col; i++){
    //     colList[i] = getList();
    //     colList[i]->type = 0;
    // }

    // for (int i = 0; i< n_shap; i++){
    //     shapList[i] = getList();
    //     shapList[i]->type = 1;
    // }

    // char running = 1;
    // SDL_Event event;

    // SDL_Surface * txt_score;
    // SDL_Texture * tex;
    // SDL_Rect Rect_Score;
    // Rect_Score.x = 17;
    // Rect_Score.y = 10;
    // TTF_Font * font = TTF_OpenFont("./Assets/Fonts/VeniteAdoremus-rgRBA.ttf", 28);
    // TTF_Font * fontSmall = TTF_OpenFont("./Assets/Fonts/VeniteAdoremus-rgRBA.ttf", 14);

    // int score = 0;
    // int nscore = 0;
    // char * score_str;
    // char insert = 0;
    // char side;
    // char update = 1;
    // int d_col = 256*6/n_col;
    // int r;
    // int g;
    // int b;
    // int x;
    // int y;

    // // Text
    // SDL_Rect rect_Next;
    // SDL_Surface * txt_next = TTF_RenderText_Blended(fontSmall, "Next :", white);
    // SDL_Texture * tex_next = SDL_CreateTextureFromSurface(rend, txt_next);
    // rect_Next.w = txt_next->w;
    // rect_Next.h = txt_next->h;
    // SDL_FreeSurface(txt_next);
    // rect_Next.x = 700;
    // rect_Next.y = 565;

    // //Utilities
    // Forme * ID[5] = {NULL, NULL, NULL, NULL, NULL}; //will store the IDs (pointer to Forme) of the the shapes to remove from the Lists
    // Forme * next[5]; //will store the next 5 shapes to play

    // for (int i = 0; i<5; i++){
    //     next[i] = getRandForme(n_shap, n_col);
    // }

    // while (running){
        
    //     while (SDL_PollEvent(&event))
    //     {
    //         switch (event.type)
    //         {
    //             case SDL_QUIT:
    //                 running = 0;
    //                 break;
    //             case SDL_KEYDOWN:
    //                 switch (event.key.keysym.scancode) {
    //                     case SDL_SCANCODE_LEFT:
    //                         insert = 1;
    //                         side = 0;
    //                         update = 1;
    //                         break;
    //                     case SDL_SCANCODE_RIGHT:
    //                         insert = 1;
    //                         side = 1;
    //                         update = 1;
    //                         break;
    //                     case SDL_SCANCODE_C:
    //                         rotateMlist4(mainlist, colList[0], colList, shapList, n_col, n_shap);
    //                         update = 1;
    //                         break;
    //                     case SDL_SCANCODE_F:
    //                         rotateMlist4(mainlist, shapList[0], colList, shapList, n_col, n_shap);
    //                         update = 1;
    //                         break;
    //                     default:
    //                         break;
    //                 }
    //                 break;
    //             default:
    //                 break;
    //         }
    //     }
    //     if (insert){
    //         appendMainListe(mainlist, next[0], (int)side);
    //         appendMainListe(colList[(int)next[0]->col], next[0], (int)side);
    //         appendMainListe(shapList[(int)next[0]->type], next[0], (int)side);
    //         for (int i = 0; i<4; i++){
    //             next[i] = next[i+1];
    //         }
    //         next[4] = getRandForme(n_shap, n_col);
    //     }

    //     nscore = 1;
    //     while (nscore != 0){
    //         nscore = checkListe(mainlist, ID);
    //         score += nscore;
    //         remAllListe(ID, mainlist, colList, shapList, nscore, n_col, n_shap);
    //     }

    //     insert = 0;

    //     if (update){
    //         // Clear screen
    //         SDL_SetRenderDrawColor(rend, 0, 0, 32, 6);
    //         SDL_RenderClear(rend);
    //         SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

    //         // Display score
    //         score_str = scoreString(score);
    //         txt_score = TTF_RenderText_Blended(font, score_str, white);
    //         tex = SDL_CreateTextureFromSurface(rend, txt_score);
    //         Rect_Score.w = txt_score->w;
    //         Rect_Score.h = txt_score->h;
    //         SDL_FreeSurface(txt_score);
    //         SDL_RenderCopy(rend, tex, NULL, &Rect_Score);
    //         SDL_DestroyTexture(tex);

    //         // Display mainlist
    //         Maillon * m = mainlist->first;

    //         for(int i = 0; i<mainlist->length; i++){
    //             colorFromNumber((m->f->col)*d_col, &r, &g, &b);
    //             x = (WIDTH-(mainlist->length)*60)/2+i*60+30;
    //             y = HEIGHT/2;
    //             drawpoly(rend, m->f->type+3, x, y, 50, r, g, b);
    //             if (m->f->type > 3){
    //                 draw_edges_number(rend, fontSmall, m->f->type+3, x, y);
    //             }
    //             m = m->next;
    //         }

    //         // Display next piece
    //         colorFromNumber((next[0]->col)*d_col, &r, &g, &b);
    //         x = (WIDTH)/2;
    //         y = HEIGHT-140;
    //         drawpoly(rend, next[0]->type+3, x, y, 70, r, g, b);
    //         if (next[0]->type > 3){
    //             draw_edges_number(rend, fontSmall, next[0]->type+3, x, y);
    //         }

    //         // Display next 4 pieces
    //         for(int i = 1; i<5; i++){
    //             colorFromNumber((next[i]->col)*d_col, &r, &g, &b);
    //             x = (WIDTH-60)/2+i*60+50;
    //             y = HEIGHT-100;
    //             drawpoly(rend, next[i]->type+3, x, y, 50, r, g, b);
    //             if (next[i]->type > 3){
    //                 draw_edges_number(rend, fontSmall, next[i]->type+3, x, y);
    //             }
    //         }
    //         SDL_RenderCopy(rend, tex_next, NULL, &rect_Next);

    //         for (int i = 0; i<n_col; i++){
    //             // char txt[2];
    //             // *txt = '1' + (char)i;
    //             // SDL_RenderDrawText(rend, font, i*40+50, 550, txt);
    //             colorFromNumber(i*d_col, &r, &g, &b);
    //             aacircleRGBA(rend, i*50+50, 550, 15, r, g, b, 255);
    //             filledCircleRGBA(rend, i*50+50, 550, 15, r, g, b, 255);
    //         }

    //         for (int i = 0; i<n_col; i++){
    //             // char txt[2];
    //             // *txt = '1' + (char)i;
    //             // SDL_RenderDrawText(rend, font, i*40+50, 550, txt);
    //             drawpoly(rend, i+3, i*50+50, 600, 35, 255, 255, 255);
    //             draw_edges_number(rend, fontSmall, i+3, i*50+50, 630);
    //         }

    //         update = 0;
    //     }

    //     if (mainlist->length>=max_shapes){
    //         running = 0;
    //     }

    //     SDL_RenderPresent(rend);
    //     SDL_Delay(1000/FPS);
    // }
    // for (int i = 0; i<5; i++){
    //     free(next[i]);
    //     if (ID[i] != NULL){
    //         free(ID[i]);
    //     }
    // }
    return 0;
}

int mainMenuSDL(void){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() != 0){
        printf("Error initializing SDL_ttf: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window* wind = SDL_CreateWindow("Tetriste",
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

    SDL_Surface * icon = IMG_Load("./Assets/icon.png");
    if (icon == NULL) {
        printf("L'icône n'a pas pu être chargée! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetWindowIcon(wind, icon);
    SDL_FreeSurface(icon);

    SDL_Rect rect_Title;
    TTF_Font * fontBig = TTF_OpenFont("./Assets/Fonts/VeniteAdoremus-rgRBA.ttf", 72);
    TTF_SetFontHinting(fontBig, TTF_HINTING_NORMAL);

    SDL_Surface * txt_title = TTF_RenderText_Blended(fontBig, "Temajorant", white);
    SDL_Texture * tex_title = SDL_CreateTextureFromSurface(rend, txt_title);
    rect_Title.w = txt_title->w;
    rect_Title.h = txt_title->h;
    SDL_FreeSurface(txt_title);
    rect_Title.x = (WIDTH-rect_Title.w)/2;
    rect_Title.y = 100;

    SDL_Texture * tex;

    SDL_Texture * right_arrow = getTexFromImg(rend, "./Assets/Keys/Arrow-R-Key.png");
    SDL_Texture * left_arrow = getTexFromImg(rend, "./Assets/Keys/Arrow-L-Key.png");
    SDL_Rect rect_inc_col_src = {0, 0, 32, 32};
    SDL_Rect rect_inc_col_dst = {400, 350, 50, 50};
    SDL_Rect rect_dec_col_src = {0, 0, 32, 32};
    SDL_Rect rect_dec_col_dst = {250, 350, 50, 50};

    SDL_Rect rect_inc_sha_src = {0, 0, 32, 32};
    SDL_Rect rect_inc_sha_dst = {1005, 350, 50, 50};
    SDL_Rect rect_dec_sha_src = {0, 0, 32, 32};
    SDL_Rect rect_dec_sha_dst = {855, 350, 50, 50};

    SDL_Rect rect_n_col;
    SDL_Rect rect_n_sha;

    int n_col = 4;
    int n_sha = 4;
    char * col_str;
    char * sha_str;
    SDL_Surface * col_sur;
    SDL_Surface * sha_sur;

    char running = 1;
    char quit = 0;
    SDL_Event event;

    while (running){
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = 0;
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_SPACE:
                            running = 0;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (ButtonClick(&event, &rect_dec_col_dst)){
                        n_col = max(2, n_col-1);
                    }
                    if (ButtonClick(&event, &rect_inc_col_dst)){
                        n_col = min(9, n_col+1);
                    }
                    if (ButtonClick(&event, &rect_dec_sha_dst)){
                        n_sha = max(2, n_sha-1);
                    }
                    if (ButtonClick(&event, &rect_inc_sha_dst)){
                        n_sha = min(9, n_sha+1);
                    }
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(rend, 0, 0, 32, 6);
        SDL_RenderClear(rend);
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        
        // Draw arrows
        SDL_RenderCopy(rend, right_arrow, &rect_inc_col_src, &rect_inc_col_dst);
        SDL_RenderCopy(rend, left_arrow, &rect_dec_col_src, &rect_dec_col_dst);
        SDL_RenderCopy(rend, right_arrow, &rect_inc_sha_src, &rect_inc_sha_dst);
        SDL_RenderCopy(rend, left_arrow, &rect_dec_sha_src, &rect_dec_sha_dst);


        // Draw number of colors
        col_str = intToString(n_col);
        col_sur = TTF_RenderText_Blended(fontBig, col_str, white);
        tex = SDL_CreateTextureFromSurface(rend, col_sur);
        rect_n_col.x = 350-col_sur->w/2;
        rect_n_col.y = 350-col_sur->h/2;
        rect_n_col.w = col_sur->w;
        rect_n_col.h = col_sur->h;
        SDL_FreeSurface(col_sur);
        SDL_RenderCopy(rend, tex, NULL, &rect_n_col);
        SDL_DestroyTexture(tex);

        // Draw number of shapes
        sha_str = intToString(n_sha);
        sha_sur = TTF_RenderText_Blended(fontBig, sha_str, white);
        tex = SDL_CreateTextureFromSurface(rend, sha_sur);
        rect_n_sha.x = 955-sha_sur->w/2;
        rect_n_sha.y = 350-sha_sur->h/2;
        rect_n_sha.w = sha_sur->w;
        rect_n_sha.h = sha_sur->h;
        SDL_FreeSurface(sha_sur);
        SDL_RenderCopy(rend, tex, NULL, &rect_n_sha);
        SDL_DestroyTexture(tex);

        // Draw Title text
        SDL_RenderCopy(rend, tex_title, NULL, &rect_Title);

        SDL_RenderPresent(rend);
        SDL_Delay(1000/60);

        
    }
    SDL_DestroyTexture(right_arrow);
    SDL_DestroyTexture(left_arrow);
    SDL_DestroyTexture(tex_title);
    SDL_DestroyTexture(tex);
    if (!quit){
        mainLoopSDL(rend, n_col, n_sha, 15);
    }
    SDL_DestroyWindow(wind);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
    return 0;
}

void mainloopASCII(char debug){
    int n_color = 4;
    int n_shape = 4;

    Liste ** colList = malloc(sizeof(Liste *) * n_color);
    Liste ** shapList = malloc(sizeof(Liste *) * n_shape);

    Liste * mainlist = getList();

    for (int i = 0; i< n_color; i++){
        colList[i] = getList();
    }

    for (int i = 0; i< n_shape; i++){
        shapList[i] = getList();
    }

    int score = 0;
    int nscore = 0;
    char move;
    char r_id;
    char insert = 0;
    char side = 0;

    Forme * ID[5];

    Forme * next[5];

    for (int i = 0; i<5; i++){
        next[i] = getRandForme(n_shape, n_color);
    }

    char * types = "TRCL";

    while (mainlist->length < 15){
        if (insert){
            for (int i = 0; i<4; i++){
                next[i] = next[i+1];
            }
            next[4] = getRandForme(n_shape, n_color);
        }

        insert = 0;

        printState(mainlist, score, next);
        if (debug){
            for (int j = 0; j < n_shape; j++){
                printf("\n");
                printList(shapList[j]);
            }
            for (int j = 0; j < n_shape; j++){
                printf("\n");
                printList(colList[j]);
            }
        }

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
                printf("Which shape to rotate ?\n| ");
                for(int i = 0; i < n_shape; i++){
                    printf("%d - %c | ", i, types[i]);
                }
                printf("\n");
                scanf(" %c", &r_id);
                rotateMlist4(mainlist, shapList[(int)(r_id-'0')], colList, shapList, n_color, n_shape);
                break;
            case 'c':
                printf("Which color to rotate ?\n| ");
                for(int i = 0; i < n_color; i++){
                    printf("%d - \033[3%dm\xdb\xdb\x1b[0m |", i, i+1);
                }
                printf("\n");
                scanf(" %c", &r_id);
                rotateMlist4(mainlist, colList[(int)(r_id-'0')], colList, shapList, n_color, n_shape);
                break;
            default:
                break;
        }

        if (insert){
            appendMainListe(mainlist, next[0], (int)side);
            appendMainListe(colList[(int)next[0]->col], next[0], (int)side);
            appendMainListe(shapList[(int)next[0]->type], next[0], (int)side);
        }

        nscore = 1;
        while (nscore != 0){
            nscore = checkListe(mainlist, ID);
            score += nscore;
            if (!insert && nscore > 0){
                score += 2; // bonus 2 points if rotation
            }
            remAllListe(ID, mainlist, colList, shapList, nscore, n_color, n_shape);
        }
    }

    printf("Game over !");

    for (int i = 0; i<5; i++){
        free(next[i]);
        // if (ID[i] != NULL){
        //     free(ID[i]);
        // }
    }
    for (int i = 0; i < n_shape; i++){
        freeListe(shapList[i]);
    }
    //free(shapList);
    for (int i = 0; i < n_color; i++){
        freeListe(colList[i]);
    }
    free(shapList);
    free(colList);
    //free(colList);
    freeMainListe(mainlist);
}

void debug(){
    setupConsole();

    // Liste * mainlist = getList();

    // // f = getRandForme(4, 4);
    // appendMainListe(mainlist, getRandForme(4, 4), 1);

    // // f = getRandForme(4, 4);
    // appendMainListe(mainlist, getRandForme(4, 4), 1);

    // //mainlist->first->prev->mainID = 2;
    // printList(mainlist);
    // restoreConsole();

    // freeMainListe(mainlist);

    restoreConsole();
}

int main(int argc, char *argv[]) {
    
    if (argc <= 1){
        printf("Please provide an argument");
        return 0;
    }

    srand(time(NULL));

    if (!strcmp(argv[1], "ASCII")){
        setupConsole();
        if (argc >= 3 && !strcmp(argv[2], "debug")){
            mainloopASCII(1);    
        } else {
            mainloopASCII(0);
        }
        restoreConsole();
    } else if (!strcmp(argv[1], "SDL")){
        mainMenuSDL();
    }
    return 0;
}