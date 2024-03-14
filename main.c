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

void remAllListe(Piece ** rem, Liste * mainlist, Liste ** colList, Liste ** shapList, int len, int n_col, int n_shap){
    for (int i = 0; i<len; i++){
        remListe(mainlist, rem[i]);

        remListe(colList[(int)rem[i]->col], rem[i]);

        remListe(shapList[(int)rem[i]->shape], rem[i]);

        free(rem[i]);
    }
}

int mainLoopSDL(SDL_Renderer * rend, int n_col, int n_shap, int max_shapes, char load, int * score, int * quit){


    Liste * mainlist = getList();
    Piece * next[5]; //will store the next 5 shapes to play
    *score = 0;

    if (load){
        loadgame(mainlist, next, score, &n_col, &n_shap, &max_shapes);
    }

    Liste ** colList = malloc(sizeof(Liste *) * n_col);
    Liste ** shapList = malloc(sizeof(Liste *) * n_shap);

    for (int i = 0; i< n_col; i++){
        colList[i] = getList();
        colList[i]->type = 0;
    }

    for (int i = 0; i< n_shap; i++){
        shapList[i] = getList();
        shapList[i]->type = 1;
    }

    if (load){
        Maillon * m = mainlist->first;
        printf("%d %d ", m->f->col, m->f->shape);
        for (int i = 0; i < mainlist->length; i++){
            appendListe(colList[(int)m->f->col], m->f, 1);
            appendListe(shapList[(int)m->f->shape], m->f, 1);
            m = m->next;
        }
    }

    char running = 1;
    SDL_Event event;

    SDL_Surface * txt_score;
    SDL_Surface * txt_n_shapes;
    SDL_Texture * tex;
    SDL_Rect Rect_Score;
    Rect_Score.x = 17;
    Rect_Score.y = 10;
    SDL_Rect Rect_n_shapes;
    Rect_n_shapes.x = 1100;
    Rect_n_shapes.y = 10;
    TTF_Font * font = TTF_OpenFont("./Assets/Fonts/VeniteAdoremus-rgRBA.ttf", 28);
    TTF_Font * fontSmall = TTF_OpenFont("./Assets/Fonts/VeniteAdoremus-rgRBA.ttf", 14);

    int nscore = 0;
    char insert = 0;
    char side;
    char update = 1;
    int d_col = 256*6/n_col;
    int r;
    int g;
    int b;
    int x;
    int y;
    
    // Text
    SDL_Rect rect_Next;
    SDL_Surface * txt_next = TTF_RenderText_Blended(fontSmall, "Next :", white);
    SDL_Texture * tex_next = SDL_CreateTextureFromSurface(rend, txt_next);
    rect_Next.w = txt_next->w;
    rect_Next.h = txt_next->h;
    SDL_FreeSurface(txt_next);
    rect_Next.x = 700;
    rect_Next.y = 565;

    //Buttons
    SDL_Texture * right_arrow = getTexFromImg(rend, "./Assets/Keys/Arrow-R-Key.png");
    SDL_Texture * left_arrow = getTexFromImg(rend, "./Assets/Keys/Arrow-L-Key.png");
    SDL_Rect rect_left_src = {0, 0, 32, 32};
    SDL_Rect rect_left_dst = {10, HEIGHT/2-25, 50, 50};

    SDL_Rect rect_right_src = {0, 0, 32, 32};
    SDL_Rect rect_right_dst = {WIDTH-60, HEIGHT/2-25, 50, 50};

    //Utilities
    Piece * ID[5] = {NULL, NULL, NULL, NULL, NULL}; //will store the IDs (pointer to Piece) of the the shapes to remove from the Lists

    if (!load){
        for (int i = 0; i<5; i++){
            next[i] = getRandPiece(n_shap, n_col);
        }
    }

    while (running){
        
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = 0;
                    *quit = 1;
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
                        case SDL_SCANCODE_C:
                            rotateMList4(mainlist, colList[0], colList, shapList, n_col, n_shap);
                            update = 1;
                            break;
                        case SDL_SCANCODE_F:
                            rotateMList4(mainlist, shapList[0], colList, shapList, n_col, n_shap);
                            update = 1;
                            break;
                        case SDL_SCANCODE_S:
                            savegame(mainlist, next, *score, n_col, n_shap, max_shapes);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (ButtonClick(&event, &rect_left_dst)){
                        insert = 1;
                        side = 0;
                        update = 1;
                        break;
                    }
                    if (ButtonClick(&event, &rect_right_dst)){
                        insert = 1;
                        side = 1;
                        update = 1;
                        break;
                    }
                    if (35 <= event.button.x && event.button.x <= (n_col+1)*50+30 && 535 <= event.button.y && event.button.y <= 615){
                        int i = ceil((event.button.x+15)/50-1);
                        printf("%d", i);
                        if (event.button.x <= (i+1)*50+15){
                            if (535 <= event.button.y && event.button.y <= 565){
                                rotateMList4(mainlist, colList[i], colList, shapList, n_col, n_shap);
                                update = 1;
                            }
                            if (585 <= event.button.y && event.button.y <= 615){
                                rotateMList4(mainlist, shapList[i], colList, shapList, n_col, n_shap);
                                update = 1;
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        if (insert){
            appendListe(mainlist, next[0], (int)side);
            appendListe(colList[(int)next[0]->col], next[0], (int)side);
            appendListe(shapList[(int)next[0]->shape], next[0], (int)side);
            for (int i = 0; i<4; i++){
                next[i] = next[i+1];
            }
            next[4] = getRandPiece(n_shap, n_col);
        }

        nscore = 1;
        while (nscore != 0){
            nscore = checkListe(mainlist, ID);
            *score += nscore;
            remAllListe(ID, mainlist, colList, shapList, nscore, n_col, n_shap);
        }

        insert = 0;

        if (update){
            // Clear screen
            SDL_SetRenderDrawColor(rend, 0, 0, 32, 6);
            SDL_RenderClear(rend);
            SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

            // Display score
            txt_score = TTF_RenderText_Blended(font, scoreString(*score), white);
            tex = SDL_CreateTextureFromSurface(rend, txt_score);
            Rect_Score.w = txt_score->w;
            Rect_Score.h = txt_score->h;
            SDL_FreeSurface(txt_score);
            SDL_RenderCopy(rend, tex, NULL, &Rect_Score);
            SDL_DestroyTexture(tex);


            // Display number of shapes
            txt_n_shapes = TTF_RenderText_Blended(font, shapeString(mainlist->length), white);
            tex = SDL_CreateTextureFromSurface(rend, txt_n_shapes);
            Rect_n_shapes.x = WIDTH - 17 - txt_n_shapes->w;
            Rect_n_shapes.w = txt_n_shapes->w;
            Rect_n_shapes.h = txt_n_shapes->h;
            SDL_FreeSurface(txt_n_shapes);
            SDL_RenderCopy(rend, tex, NULL, &Rect_n_shapes);
            SDL_DestroyTexture(tex);

            // Display mainlist
            Maillon * m = mainlist->first;

            for(int i = 0; i<mainlist->length; i++){
                colorFromNumber((m->f->col)*d_col, &r, &g, &b);
                x = (WIDTH-(mainlist->length)*60)/2+i*60+30;
                y = HEIGHT/2;
                drawpoly(rend, m->f->shape+3, x, y, 50, r, g, b);
                if (m->f->shape > 3){
                    draw_edges_number(rend, fontSmall, m->f->shape+3, x, y);
                }
                m = m->next;
            }

            // Display next piece
            colorFromNumber((next[0]->col)*d_col, &r, &g, &b);
            x = (WIDTH)/2;
            y = HEIGHT-140;
            drawpoly(rend, next[0]->shape+3, x, y, 70, r, g, b);
            if (next[0]->shape > 3){
                draw_edges_number(rend, fontSmall, next[0]->shape+3, x, y);
            }

            // Display next 4 pieces
            for(int i = 1; i<5; i++){
                colorFromNumber((next[i]->col)*d_col, &r, &g, &b);
                x = (WIDTH-60)/2+i*60+50;
                y = HEIGHT-100;
                drawpoly(rend, next[i]->shape+3, x, y, 50, r, g, b);
                if (next[i]->shape > 3){
                    draw_edges_number(rend, fontSmall, next[i]->shape+3, x, y);
                }
            }
            SDL_RenderCopy(rend, tex_next, NULL, &rect_Next);

            // Display buttons
            SDL_RenderCopy(rend, left_arrow, &rect_left_src, &rect_left_dst);
            SDL_RenderCopy(rend, right_arrow, &rect_right_src, &rect_right_dst);
            for (int i = 0; i<n_col; i++){
                colorFromNumber(i*d_col, &r, &g, &b);
                aacircleRGBA(rend, i*50+50, 550, 15, r, g, b, 255);
                filledCircleRGBA(rend, i*50+50, 550, 15, r, g, b, 255);
            }

            for (int i = 0; i<n_shap; i++){
                drawpoly(rend, i+3, i*50+50, 600, 35, 255, 255, 255);
                draw_edges_number(rend, fontSmall, i+3, i*50+50, 630);
            }

            update = 0;
        }

        if (mainlist->length>=max_shapes){
            running = 0;
        }

        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);
    }
    SDL_DestroyTexture(right_arrow);
    SDL_DestroyTexture(left_arrow);
    SDL_DestroyTexture(tex_next);
    for (int i = 0; i<5; i++){
        free(next[i]);
    }
    for (int i = 0; i < n_shap; i++){
        freeListe(shapList[i]);
    }
    for (int i = 0; i < n_col; i++){
        freeListe(colList[i]);
    }
    free(shapList);
    free(colList);
    freeMainListe(mainlist);

    return 0;
}

int mainMenuSDL(SDL_Renderer * rend, int * n_col, int * n_sha, int * max_pieces, char * load, int * quit){

    // Text
    TTF_Font * fontBig = TTF_OpenFont("./Assets/Fonts/VeniteAdoremus-rgRBA.ttf", 72);
    TTF_Font * font = TTF_OpenFont("./Assets/Fonts/VeniteAdoremus-rgRBA.ttf", 28);
    TTF_SetFontHinting(fontBig, TTF_HINTING_NORMAL);

    SDL_Rect rect_Title;
    SDL_Surface * txt_title = TTF_RenderText_Blended(fontBig, "Temajorant", white);
    SDL_Texture * tex_title = SDL_CreateTextureFromSurface(rend, txt_title);
    rect_Title.w = txt_title->w;
    rect_Title.h = txt_title->h;
    SDL_FreeSurface(txt_title);
    rect_Title.x = (WIDTH-rect_Title.w)/2;
    rect_Title.y = 100;

    SDL_Rect rect_start;
    SDL_Surface * txt_start = TTF_RenderText_Blended(font, "Press space to start", white);
    SDL_Texture * tex_start = SDL_CreateTextureFromSurface(rend, txt_start);
    rect_start.x = (WIDTH-txt_start->w)/2;
    rect_start.y = 650;
    rect_start.w = txt_start->w;
    rect_start.h = txt_start->h;
    SDL_FreeSurface(txt_start);

    // Parameters count
    SDL_Rect rect_shapes_title;
    SDL_Surface * title_shapes = TTF_RenderText_Blended(font, "Shapes", white);
    SDL_Texture * tex_shapes = SDL_CreateTextureFromSurface(rend, title_shapes);
    rect_shapes_title.w = title_shapes->w;
    rect_shapes_title.h = title_shapes->h;
    rect_shapes_title.x = 955-title_shapes->w/2;
    rect_shapes_title.y = 410;
    SDL_FreeSurface(title_shapes);

    SDL_Rect rect_col_title;
    SDL_Surface * title_col = TTF_RenderText_Blended(font, "Colors", white);
    SDL_Texture * tex_col = SDL_CreateTextureFromSurface(rend, title_col);
    rect_col_title.w = title_col->w;
    rect_col_title.h = title_col->h;
    rect_col_title.x = 350-title_col->w/2;
    rect_col_title.y = 410;
    SDL_FreeSurface(title_col);

    SDL_Rect rect_pie_title;
    SDL_Surface * title_pie = TTF_RenderText_Blended(font, "Pieces", white);
    SDL_Texture * tex_pie = SDL_CreateTextureFromSurface(rend, title_pie);
    rect_pie_title.w = title_pie->w;
    rect_pie_title.h = title_pie->h;
    rect_pie_title.x = WIDTH/2-title_pie->w/2;
    rect_pie_title.y = 410;
    SDL_FreeSurface(title_pie);

    // Assets & assets rects
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

    SDL_Rect rect_inc_pie_src = {0, 0, 32, 32};
    SDL_Rect rect_inc_pie_dst = {WIDTH/2+50, 350, 50, 50};
    SDL_Rect rect_dec_pie_src = {0, 0, 32, 32};
    SDL_Rect rect_dec_pie_dst = {WIDTH/2-100, 350, 50, 50};

    // Other variables
    SDL_Rect rect_n_col;
    SDL_Rect rect_n_sha;
    SDL_Rect rect_n_pie;

    *n_col = 4;
    *n_sha = 4;
    *max_pieces = 15;
    char * col_str;
    char * sha_str;
    char * pie_str;
    SDL_Surface * col_sur;
    SDL_Surface * sha_sur;
    SDL_Surface * pie_sur;

    char running = 1;
    *quit = 0;
    load = 0;
    SDL_Event event;

    while (running){
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = 0;
                    *quit = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_SPACE:
                            running = 0;
                            break;
                        case SDL_SCANCODE_S:
                            running = 0;
                            *load = 1;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (ButtonClick(&event, &rect_dec_col_dst)){
                        *n_col = max(2, *n_col-1);
                    }
                    if (ButtonClick(&event, &rect_inc_col_dst)){
                        *n_col = min(9, *n_col+1);
                    }
                    if (ButtonClick(&event, &rect_dec_sha_dst)){
                        *n_sha = max(2, *n_sha-1);
                    }
                    if (ButtonClick(&event, &rect_inc_sha_dst)){
                        *n_sha = min(9, *n_sha+1);
                    }
                    if (ButtonClick(&event, &rect_dec_pie_dst)){
                        *max_pieces = max(10, *max_pieces-1);
                    }
                    if (ButtonClick(&event, &rect_inc_pie_dst)){
                        *max_pieces = min(30, *max_pieces+1);
                    }
                    break;
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
        SDL_RenderCopy(rend, right_arrow, &rect_inc_pie_src, &rect_inc_pie_dst);
        SDL_RenderCopy(rend, left_arrow, &rect_dec_pie_src, &rect_dec_pie_dst);


        // Draw number of colors
        col_str = intToString(*n_col);
        col_sur = TTF_RenderText_Blended(fontBig, col_str, white);
        tex = SDL_CreateTextureFromSurface(rend, col_sur);
        rect_n_col.x = 350-col_sur->w/2;
        rect_n_col.y = 350-col_sur->h/2;
        rect_n_col.w = col_sur->w;
        rect_n_col.h = col_sur->h;
        SDL_FreeSurface(col_sur);
        SDL_RenderCopy(rend, tex, NULL, &rect_n_col);
        SDL_DestroyTexture(tex);

        SDL_RenderCopy(rend, tex_col, NULL, &rect_col_title);

        // Draw number of shapes
        sha_str = intToString(*n_sha);
        sha_sur = TTF_RenderText_Blended(fontBig, sha_str, white);
        tex = SDL_CreateTextureFromSurface(rend, sha_sur);
        rect_n_sha.x = 955-sha_sur->w/2;
        rect_n_sha.y = 350-sha_sur->h/2;
        rect_n_sha.w = sha_sur->w;
        rect_n_sha.h = sha_sur->h;
        SDL_FreeSurface(sha_sur);
        SDL_RenderCopy(rend, tex, NULL, &rect_n_sha);
        SDL_DestroyTexture(tex);

        SDL_RenderCopy(rend, tex_shapes, NULL, &rect_shapes_title);

        // Draw number of pieces
        pie_str = intToString(*max_pieces);
        pie_sur = TTF_RenderText_Blended(fontBig, pie_str, white);
        tex = SDL_CreateTextureFromSurface(rend, pie_sur);
        rect_n_pie.x = WIDTH/2-pie_sur->w/2;
        rect_n_pie.y = 350-pie_sur->h/2;
        rect_n_pie.w = pie_sur->w;
        rect_n_pie.h = pie_sur->h;
        SDL_FreeSurface(pie_sur);
        SDL_RenderCopy(rend, tex, NULL, &rect_n_pie);
        SDL_DestroyTexture(tex);

        SDL_RenderCopy(rend, tex_pie, NULL, &rect_pie_title);

        // Draw text
        SDL_RenderCopy(rend, tex_title, NULL, &rect_Title);
        SDL_RenderCopy(rend, tex_start, NULL, &rect_start);

        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);

        
    }
    SDL_DestroyTexture(right_arrow);
    SDL_DestroyTexture(left_arrow);
    SDL_DestroyTexture(tex_title);
    SDL_DestroyTexture(tex);
    return 0;
}

int endScreenSDL(SDL_Renderer * rend, int score, int * quit){
    char running = 1;

    TTF_Font * fontBig = TTF_OpenFont("./Assets/Fonts/VeniteAdoremus-rgRBA.ttf", 72);
    TTF_Font * font = TTF_OpenFont("./Assets/Fonts/VeniteAdoremus-rgRBA.ttf", 28);

    SDL_Rect rect_gover;
    SDL_Surface * txt_gover = TTF_RenderText_Blended(fontBig, "Game Over !", white);
    SDL_Texture * tex_gover = SDL_CreateTextureFromSurface(rend, txt_gover);
    rect_gover.w = txt_gover->w;
    rect_gover.h = txt_gover->h;
    SDL_FreeSurface(txt_gover);
    rect_gover.x = (WIDTH-rect_gover.w)/2;
    rect_gover.y = 50;

    SDL_Rect rect_quit;
    SDL_Surface * txt_quit = TTF_RenderText_Blended(font, "Quit game", white);
    SDL_Texture * tex_quit = SDL_CreateTextureFromSurface(rend, txt_quit);
    rect_quit.x = (WIDTH/2-300)-txt_quit->w/2;
    rect_quit.y = 600;
    rect_quit.w = txt_quit->w;
    rect_quit.h = txt_quit->h;
    SDL_FreeSurface(txt_quit);

    SDL_Rect rect_replay;
    SDL_Surface * txt_again = TTF_RenderText_Blended(font, "Play again", white);
    SDL_Texture * tex_again = SDL_CreateTextureFromSurface(rend, txt_again);
    rect_replay.x = (WIDTH/2+300)-txt_again->w/2;
    rect_replay.y = 600;
    rect_replay.w = txt_again->w;
    rect_replay.h = txt_again->h;
    SDL_FreeSurface(txt_again);

    SDL_Event event;

    char ** init = malloc(sizeof(char*) * 10);
    for (int i = 0; i<10; i++){
        init[i] = malloc(sizeof(char)*4);
    }
    int scores[10];

    int n_scores = getScores(scores, init);
    char * score_str;
    SDL_Surface * score_sur;
    SDL_Texture * tex;
    SDL_Rect rect_score;

    char enterInit = 0;
    int i;
    for (i = 0; i<10; i++){
        if (score>scores[i]){
            enterInit = 1;
            for(int j = 9; j>i; j--){
                scores[j] = scores[j-1];
                init[j] = init[j-1];
            }
            scores[i] = score;
            break;
        }
    }


    if (enterInit) {
        char initials[4] = {' ', 0, 0, 0};
        char n_init = 0;
        SDL_Surface * inputInit = TTF_RenderText_Blended(fontBig, "Enter your initials:", white);
        SDL_Texture * inputTex = SDL_CreateTextureFromSurface(rend, inputInit);
        SDL_Rect rect_input_init;
        SDL_FreeSurface(inputInit);
        rect_input_init.x = (WIDTH - inputInit->w) / 2;
        rect_input_init.y = 200;
        rect_input_init.w = inputInit->w;
        rect_input_init.h = inputInit->h;

        SDL_Surface * inputChar;
        SDL_Texture * charTex;
        SDL_Rect rect_input_char;

        SDL_Event textEvent;
        SDL_StartTextInput();
        while(n_init < 3){
            while (SDL_PollEvent(&textEvent)) {
                if (textEvent.type == SDL_TEXTINPUT) {
                    printf("%s", textEvent.text.text);
                    initials[(int)n_init++] = textEvent.text.text[0];
                }
                if (event.type == SDL_KEYDOWN && textEvent.key.keysym.scancode == SDL_SCANCODE_BACKSPACE){
                    initials[(int)--n_init] = ' ';
                }
            }
            SDL_SetRenderDrawColor(rend, 0, 0, 32, 6);
            SDL_RenderClear(rend);

            SDL_RenderCopy(rend, inputTex, NULL, &rect_input_init);

            inputChar = TTF_RenderText_Blended(fontBig, initials, white);
            charTex = SDL_CreateTextureFromSurface(rend, inputChar);
            rect_input_char.x = (WIDTH-inputChar->w)/2;
            rect_input_char.y = HEIGHT/2;
            rect_input_char.w = inputChar->w;
            rect_input_char.h = inputChar->h;
            SDL_FreeSurface(inputChar);
            SDL_RenderCopy(rend, charTex, NULL, &rect_input_char);
            SDL_DestroyTexture(charTex);

            SDL_RenderPresent(rend);
            SDL_Delay(1000/FPS);
        }
        SDL_StopTextInput();
        
        init[min(i,9)] = initials;
        printf("%d %s ", min(i,9), init[min(i,9)]);
        loadscore(scores, init);
    }

    for (int i = 0; i<10; i++){
        printf("%d %s\n", scores[i], init[i]);
    }

    char * fscore_str = scoreString(score);
    SDL_Surface *fscore_sur;
    SDL_Texture *fscore_tex;
    SDL_Rect rect_fscore;
    fscore_sur = TTF_RenderText_Blended(font, fscore_str, white);
    fscore_tex = SDL_CreateTextureFromSurface(rend, fscore_sur);
    rect_fscore.x = (WIDTH-fscore_sur->w)/2;
    rect_fscore.y = 150;
    rect_fscore.w = fscore_sur->w;
    rect_fscore.h = fscore_sur->h;
    SDL_FreeSurface(fscore_sur);

    while (running){
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = 0;
                    *quit = 1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (ButtonClick(&event, &rect_quit)){
                        running = 0;
                        *quit = 1;
                    }
                    if (ButtonClick(&event, &rect_replay)){
                        running = 0;
                        *quit = 0;
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(rend, 0, 0, 32, 6);
        SDL_RenderClear(rend);
        
        // Game Over
        SDL_RenderCopy(rend, tex_gover, NULL, &rect_gover);

        // Final score
        SDL_RenderCopy(rend, fscore_tex, NULL, &rect_fscore);
        // Scores
        if (!*quit){
            for (int i = 0; i < n_scores; i++){
                score_str = intToString(scores[i]);
                score_sur = TTF_RenderText_Blended(font, score_str, white);
                tex = SDL_CreateTextureFromSurface(rend, score_sur);
                rect_score.x = WIDTH/2-score_sur->w-5;
                rect_score.y = 200+30*i;
                rect_score.w = score_sur->w;
                rect_score.h = score_sur->h;
                SDL_FreeSurface(score_sur);
                SDL_RenderCopy(rend, tex, NULL, &rect_score);
                SDL_DestroyTexture(tex);
                free(score_str);

                score_sur = TTF_RenderText_Blended(font, init[i], white);
                tex = SDL_CreateTextureFromSurface(rend, score_sur);
                rect_score.x = WIDTH/2+5;
                rect_score.y = 200+30*i;
                rect_score.w = score_sur->w;
                rect_score.h = score_sur->h;
                SDL_FreeSurface(score_sur);
                SDL_RenderCopy(rend, tex, NULL, &rect_score);
                SDL_DestroyTexture(tex);
            }
        }
        
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        SDL_RenderCopy(rend, tex_quit, NULL, &rect_quit);
        SDL_RenderCopy(rend, tex_again, NULL, &rect_replay);

        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);
    }
    free(init);
    SDL_DestroyTexture(tex_gover);
    SDL_DestroyTexture(tex_quit);
    SDL_DestroyTexture(tex_again);

    return 0;
}

int initSDL(void){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() != 0){
        printf("Error initializing SDL_ttf: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window* wind = SDL_CreateWindow("Temajorant",
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

    // while(1){
    // }
    int quit;
    int n_col, n_shapes, max_pieces;
    char load;
    int score;

    while(1){
        mainMenuSDL(rend, &n_col, &n_shapes, &max_pieces, &load, &quit);
        if (quit){
            break;
        }
        mainLoopSDL(rend, n_col, n_shapes, max_pieces, load, &score, &quit);
        if(quit){
            break;
        }
        endScreenSDL(rend, score, &quit);
        if(quit){
            break;
        }
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

    Piece * ID[5];

    Piece * next[5];

    for (int i = 0; i<5; i++){
        next[i] = getRandPiece(n_shape, n_color);
    }

    char * shapes = "TRCL";

    while (mainlist->length < 15){
        if (insert){
            for (int i = 0; i<4; i++){
                next[i] = next[i+1];
            }
            next[4] = getRandPiece(n_shape, n_color);
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
                    printf("%d - %c | ", i, shapes[i]);
                }
                printf("\n");
                scanf(" %c", &r_id);
                rotateMList4(mainlist, shapList[(int)(r_id-'0')], colList, shapList, n_color, n_shape);
                break;
            case 'c':
                printf("Which color to rotate ?\n| ");
                for(int i = 0; i < n_color; i++){
                    printf("%d - \033[3%dm\xdb\xdb\x1b[0m |", i, i+1);
                }
                printf("\n");
                scanf(" %c", &r_id);
                rotateMList4(mainlist, colList[(int)(r_id-'0')], colList, shapList, n_color, n_shape);
                break;
            default:
                break;
        }

        if (insert){
            appendListe(mainlist, next[0], (int)side);
            appendListe(colList[(int)next[0]->col], next[0], (int)side);
            appendListe(shapList[(int)next[0]->shape], next[0], (int)side);
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

    // // f = getRandPiece(4, 4);
    // appendListe(mainlist, getRandPiece(4, 4), 1);

    // // f = getRandPiece(4, 4);
    // appendListe(mainlist, getRandPiece(4, 4), 1);

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
        initSDL();
    }
    return 0;
}