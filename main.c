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

Liste * mainlist;

MListe ** colList;
MListe ** shapList;

SDL_Color white = {255, 255, 255};

void remAllListe(Forme ** rem, int len, int n_col, int n_shap){
    for (int i = 0; i<len; i++){
        remListe(mainlist, rem[i]);

        for (int j = 0; j<n_col; j++){
            remMListe(colList[j], rem[i]);
        }

        for (int j = 0; j<n_shap; j++){
            remMListe(shapList[j], rem[i]);
        }

        free(rem[i]);
    }
}

int mainLoopSDL(SDL_Renderer * rend, int n_col, int n_shap, int max_shapes){

    // colList = malloc(sizeof(Liste *) * n_col);
    // shapList = malloc(sizeof(Liste *) * n_shap);

    // for (int i = 0; i< n_col; i++){
    //     colList[i] = getMList();
    // }

    // for (int i = 0; i< n_shap; i++){
    //     shapList[i] = getMList();
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

    // Forme ** ID = malloc(5*sizeof(Forme *));

    // Forme ** next = malloc(5*sizeof(Forme *));

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
    //         appendListe(colList[(int)next[0]->col], next[0], (int)side);
    //         appendListe(shapList[(int)next[0]->type], next[0], (int)side);
    //         for (int i = 0; i<4; i++){
    //             next[i] = next[i+1];
    //         }
    //         next[4] = getRandForme(n_shap, n_col);
    //     }

    //     nscore = 1;
    //     while (nscore != 0){
    //         nscore = checkListe(mainlist, ID);
    //         score += nscore;
    //         remAllListe(ID, nscore, n_col, n_shap);
    //     }

    //     insert = 0;

    //     if (update){
    //         SDL_SetRenderDrawColor(rend, 0, 0, 32, 6);
    //         SDL_RenderClear(rend);
    //         SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

    //         score_str = scoreString(score);
    //         txt_score = TTF_RenderText_Solid(font, score_str, white);
    //         tex = SDL_CreateTextureFromSurface(rend, txt_score);
    //         Rect_Score.w = txt_score->w;
    //         Rect_Score.h = txt_score->h;
    //         SDL_FreeSurface(txt_score);

    //         SDL_RenderCopy(rend, tex, NULL, &Rect_Score);
    //         SDL_DestroyTexture(tex);

    //         Maillon * m = mainlist->first;

    //         for(int i = 0; i<mainlist->length; i++){
    //             colorFromNumber((m->f->col)*d_col, &r, &g, &b);
    //             x = (WIDTH-(mainlist->length)*60)/2+i*60+30;
    //             y = HEIGHT/2;
    //             drawpoly(rend, m->f->type+3, x, y, 50, r, g, b);
    //             draw_edges_number(rend, fontSmall, m->f->type+3, x, y);
    //             m = m->next;
    //         }

    //         for(int i = 0; i<5; i++){
    //             colorFromNumber((next[i]->col)*d_col, &r, &g, &b);
    //             x = (WIDTH-300)/2+i*60+30;
    //             y = HEIGHT-100;
    //             drawpoly(rend, next[i]->type+3, x, y, 50, r, g, b);
    //             draw_edges_number(rend, fontSmall, next[i]->type+3, x, y);
    //         }
    //         update = 0;
    //     }

    //     if (mainlist->length>=max_shapes){
    //         running = 0;
    //     }

    //     SDL_RenderPresent(rend);
    //     SDL_Delay(1000/FPS);
    // }
    return 0;
}

int mainMenuSDL(void){
//     if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
//         printf("Error initializing SDL: %s\n", SDL_GetError());
//         return 0;
//     }

//     if (TTF_Init() != 0){
//         printf("Error initializing SDL_ttf: %s\n", SDL_GetError());
//         return 0;
//     }

//     SDL_Window* wind = SDL_CreateWindow("Tetriste",
//                                         SDL_WINDOWPOS_CENTERED,
//                                         SDL_WINDOWPOS_CENTERED,
//                                         WIDTH, HEIGHT, 0);
//     if (!wind){
//       printf("Error creating window: %s\n", SDL_GetError());
//       SDL_Quit();
//       return 0;
//     }

//     Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
//     SDL_Renderer* rend = SDL_CreateRenderer(wind, -1, render_flags);
//     if (!rend){
//         printf("Error creating renderer: %s\n", SDL_GetError());
//         SDL_DestroyWindow(wind);
//         SDL_Quit();
//         return 0;
//     }

//     SDL_Surface * icon = IMG_Load("./Assets/icon.png");
//     if (icon == NULL) {
//         printf("L'icône n'a pas pu être chargée! SDL_Error: %s\n", SDL_GetError());
//         return 1;
//     }

//     SDL_SetWindowIcon(wind, icon);

//     SDL_Rect rect_Title;
//     TTF_Font * fontBig = TTF_OpenFont("./Assets/Fonts/VeniteAdoremus-rgRBA.ttf", 72);
//     TTF_SetFontHinting(fontBig, TTF_HINTING_NORMAL);

//     SDL_Surface * txt_title = TTF_RenderText_Solid(fontBig, "Tetriste", white);
//     SDL_Texture * tex_title = SDL_CreateTextureFromSurface(rend, txt_title);
//     rect_Title.w = txt_title->w;
//     rect_Title.h = txt_title->h;
//     SDL_FreeSurface(txt_title);
//     rect_Title.x = (WIDTH-rect_Title.w)/2;
//     rect_Title.y = 100;

//     SDL_Texture * tex;

//     SDL_Texture * right_arrow = getTexFromImg(rend, "./Assets/Keys/Arrow-R-Key.png");
//     SDL_Texture * left_arrow = getTexFromImg(rend, "./Assets/Keys/Arrow-L-Key.png");
//     SDL_Rect rect_inc_col_src = {0, 0, 32, 32};
//     SDL_Rect rect_inc_col_dst = {400, 350, 50, 50};
//     SDL_Rect rect_dec_col_src = {0, 0, 32, 32};
//     SDL_Rect rect_dec_col_dst = {250, 350, 50, 50};

//     SDL_Rect rect_inc_sha_src = {0, 0, 32, 32};
//     SDL_Rect rect_inc_sha_dst = {1005, 350, 50, 50};
//     SDL_Rect rect_dec_sha_src = {0, 0, 32, 32};
//     SDL_Rect rect_dec_sha_dst = {855, 350, 50, 50};

//     SDL_Rect rect_n_col;
//     SDL_Rect rect_n_sha;

//     int n_col = 4;
//     int n_sha = 4;
//     char * col_str;
//     char * sha_str;
//     SDL_Surface * col_sur;
//     SDL_Surface * sha_sur;

//     char running = 1;
//     SDL_Event event;

//     while (running){
//         while (SDL_PollEvent(&event))
//         {
//             switch (event.type)
//             {
//                 case SDL_QUIT:
//                     goto ici;
//                     running = 0;
//                     break;
//                 case SDL_KEYDOWN:
//                     switch (event.key.keysym.scancode) {
//                         case SDL_SCANCODE_SPACE:
//                             running = 0;
//                             break;
//                         default:
//                             break;
//                     }
//                     break;
//                 case SDL_MOUSEBUTTONUP:
//                     if (ButtonClick(&event, &rect_dec_col_dst)){
//                         n_col = max(2, n_col-1);
//                     }
//                     if (ButtonClick(&event, &rect_inc_col_dst)){
//                         n_col = min(9, n_col+1);
//                     }
//                     if (ButtonClick(&event, &rect_dec_sha_dst)){
//                         n_sha = max(2, n_sha-1);
//                     }
//                     if (ButtonClick(&event, &rect_inc_sha_dst)){
//                         n_sha = min(9, n_sha+1);
//                     }
//                 default:
//                     break;
//             }
//         }
//         SDL_SetRenderDrawColor(rend, 0, 0, 32, 6);
//         SDL_RenderClear(rend);
//         SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        
//         SDL_RenderCopy(rend, right_arrow, &rect_inc_col_src, &rect_inc_col_dst);
//         SDL_RenderCopy(rend, left_arrow, &rect_dec_col_src, &rect_dec_col_dst);
//         SDL_RenderCopy(rend, right_arrow, &rect_inc_sha_src, &rect_inc_sha_dst);
//         SDL_RenderCopy(rend, left_arrow, &rect_dec_sha_src, &rect_dec_sha_dst);

//         col_str = intToString(n_col);
//         col_sur = TTF_RenderText_Solid(fontBig, col_str, white);
//         tex = SDL_CreateTextureFromSurface(rend, col_sur);
//         rect_n_col.x = 350-col_sur->w/2;
//         rect_n_col.y = 350-col_sur->h/2;
//         rect_n_col.w = col_sur->w;
//         rect_n_col.h = col_sur->h;
//         SDL_FreeSurface(col_sur);
//         SDL_RenderCopy(rend, tex, NULL, &rect_n_col);
//         SDL_DestroyTexture(tex);

//         sha_str = intToString(n_sha);
//         sha_sur = TTF_RenderText_Solid(fontBig, sha_str, white);
//         tex = SDL_CreateTextureFromSurface(rend, sha_sur);
//         rect_n_sha.x = 955-sha_sur->w/2;
//         rect_n_sha.y = 350-sha_sur->h/2;
//         rect_n_sha.w = sha_sur->w;
//         rect_n_sha.h = sha_sur->h;
//         SDL_FreeSurface(sha_sur);
//         SDL_RenderCopy(rend, tex, NULL, &rect_n_sha);
//         SDL_DestroyTexture(tex);

//         SDL_RenderCopy(rend, tex_title, NULL, &rect_Title);

//         SDL_RenderPresent(rend);
//         SDL_Delay(1000/60);
//     }
//     SDL_DestroyTexture(tex_title);
//     SDL_DestroyTexture(tex);
//     mainLoopSDL(rend, n_col, n_sha, 15);
// ici:
//     SDL_DestroyWindow(wind);
//     SDL_DestroyRenderer(rend);
//     SDL_Quit();
    return 0;
}

void mainloopASCII(char debug){
    int n_color = 4;
    int n_shape = 4;

    colList = malloc(sizeof(MListe *) * n_color);
    shapList = malloc(sizeof(MListe *) * n_shape);

    for (int i = 0; i< n_color; i++){
        colList[i] = getMList();
    }

    for (int i = 0; i< n_shape; i++){
        shapList[i] = getMList();
    }

    int score = 0;
    int nscore = 0;
    char move;
    char r_id;
    char insert = 0;
    char side = 0;

    Forme ** ID = malloc(5*sizeof(Forme *));

    Forme ** next = malloc(5*sizeof(Forme *));

    for (int i = 0; i<5; i++){
        next[i] = getRandForme(n_shape, n_color);
    }

    //Maillon * iter;
    Maillon * Minsert;

    char * types = "TRCL";

    while (mainlist->length < 15){
        if (insert){
            for (int i = 0; i<4; i++){
                next[i] = next[i+1];
            }
            next[4] = getRandForme(n_shape, n_color);
        }

        insert = 0;

        printf("\033[2J");
        printf("\033[0;0H");
        printf("Score : %d\n", score);
        printf("\n\n\n\n");
        printList(mainlist);
        if (debug){
            for (int j = 0; j < n_shape; j++){
                printf("\n");
                printMList(shapList[j]);
            }
            for (int j = 0; j < n_shape; j++){
                printf("\n");
                printMList(colList[j]);
            }
        }

        printf("\n\n\n\n");
        printf("=>\033[3%dm%c\x1b[0m<=     next : \x1b[0m", next[0]->col+1, types[(int)next[0]->type]);
        for (int i = 1; i<5; i++){
            printf("\033[3%dm%c ", next[i]->col+1, types[(int)next[i]->type]);
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
                printf("Which shape to rotate ?\n| ");
                for(int i = 0; i < n_shape; i++){
                    printf("%d - %c | ", i, types[i]);
                }
                printf("\n");
                scanf(" %c", &r_id);
                rotateMList(shapList[(int)(r_id-'0')], 1);
                //iter = shapList[(int)(r_id-'0')]->first;

                // for (int i = 0; i<shapList[(int)(r_id-'0')]->length; i++){
                //     remListe(colList[(int)iter->prev->f->col], iter->f);
                //     printf("yoyo");
                //     appendListeWithID(colList[(int)iter->f->col], iter->f, iter->f->mainID);
                //     iter = iter->next;
                // }

                break;
            case 'c':
                printf("Which color to rotate ?\n| ");
                for(int i = 0; i < n_color; i++){
                    printf("%d - \033[3%dm\xdb\xdb\x1b[0m |", i, i+1);
                }
                printf("\n");
                scanf(" %c", &r_id);
                rotateMList(colList[(int)(r_id-'0')], 0);
                //iter = colList[(int)(r_id-'0')]->first;

                // for (int i = 0; i<colList[(int)(r_id-'0')]->length; i++){
                //     remListe(shapList[(int)iter->prev->f->type], iter->f);
                //     printf("yiyi");
                //     appendListeWithID(shapList[(int)iter->f->type], iter->f, iter->f->mainID);
                //     iter = iter->next;
                // }
                break;
            default:
                break;
        }

        printf("fini");

        if (insert){
            Minsert = appendMainListe(mainlist, next[0], (int)side);
            appendMListe(colList[(int)next[0]->col], Minsert, (int)side);
            appendMListe(shapList[(int)next[0]->type], Minsert, (int)side);
        }

        printf("yéyé");

        nscore = 1;
        while (nscore != 0){
            nscore = checkListe(mainlist, ID);
            score += nscore;
            printf("entre");
            remAllListe(ID, nscore, n_color, n_shape);
            printf("%d", nscore);
        }
        printf("zizi");
    }

    printf("Game over !");

    for (int i = 0; i<5; i++){
        free(next[i]);
    }
    free(next);

    free(ID);
}

int debug(void){
    Liste * l = getList();
    Forme * f1 = malloc(sizeof(Forme));
    getForme(0, 1, f1);
    appendListe(l, f1, 1);
    Forme *f2 = malloc(sizeof(Forme));
    getForme(0, 2, f2);
    appendListe(l, f2, 1);
    printList(l);
    Forme *f3 = malloc(sizeof(Forme));
    getForme(0, 3, f3);
    f3->mainID = 2;
    appendListeWithID(l, f3, 1);
    printList(l);
    return 0;
}

int main(int argc, char *argv[]) {
    
    if (argc <= 1){
        printf("Please provide an argument");
        return 0;
    }

    mainlist = getList();

    time_t t = time(NULL);
    srand(t);

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
    } else {
        setupConsole();
        debug();
        restoreConsole();
        printf("Unknown argument '%s'", argv[1]);
    }

    freeListe(mainlist);

    free(mainlist);

    return 0;
}