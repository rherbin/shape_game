#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ansi_escape.h"
#include "../SDL2/include/SDL2/SDL.h"
#include <math.h>
#include "../SDL2_gfx/SDL2_gfxPrimitives.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include <string.h>

#define pi 3.1415926535897932384626433832795

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

//
//
// LIST MANAGEMENT FUNCTIONS
//
//

void printList(Liste * l){
    // Print each Piece of a given Liste with ansi escape
    char shapes[] = "TRCL";
    if (l->length == 0){
        return;
    }
    Maillon * m = l->first;
    for (int i = 0; i<l->length; i++){
        printf("\033[3%dm%c\x1b[0m ", m->f->col+1, shapes[(int)m->f->shape]);
        //printf("m->f:%p m:%p", m->f, m);
        m = m->next;
    }
}

#ifdef _WIN32

void printState(Liste * mainlist, int score, Piece ** next){
    char shapes[] = "TRCL";
    printf("\033[2J");
    printf("\033[0;0H");
    printf("\xda");
    for (int i = 0; i < 69; i++){
        printf("\xc4");
    }
    printf("\xbf\n");
    printf("\xb3");
    for (int i = 0; i < 31; i++){
        printf(" ");
    }
    printf("Score : %d", score);
    for (int i = 0; i< 30-max((floor(log10(score))+1), 1); i++){
        printf(" ");
    }
    printf("\xb3\n");
    printf("\xc3");
    for (int i = 0; i < 69; i++){
        printf("\xc4");
    }
    printf("\xb4\n");

    printf("\xb3");
    for (int i = 0; i<69; i++){
        printf(" ");
    }
    printf("\xb3\n");
    printf("\xb3");
    for (int i = 0; i<69; i++){
        printf(" ");
    }
    printf("\xb3\n");
    printf("\xb3");
    for (int i = 0; i < 35-mainlist->length; i++){
        printf(" ");
    }
    printList(mainlist);
    for (int i = 0; i < 34-mainlist->length; i++){
        printf(" ");
    }
    printf("\xb3\n");
    printf("\xb3");
    for (int i = 0; i<69; i++){
        printf(" ");
    }
    printf("\xb3\n");
    printf("\xb3");
    for (int i = 0; i<69; i++){
        printf(" ");
    }
    printf("\xb3\n");

    printf("\xc3");
    for (int i = 0; i < 69; i++){
        printf("\xc4");
    }
    printf("\xb4\n");

    printf("\xb3");
    for (int i = 0; i < 34; i++){
        printf(" ");
    }
    printf("\x1f");
    for (int i = 0; i < 34; i++){
        printf(" ");
    }
    printf("\xb3\n");
    printf("\xb3");
    for (int i = 0; i < 32; i++){
        printf(" ");
    }
    printf("\x10 \033[3%dm%c\x1b[0m \x11  Next : \x1b[0m", next[0]->col+1, shapes[(int)next[0]->shape]);
    for (int i = 1; i<5; i++){
        printf("\033[3%dm%c\x1b[0m ", next[i]->col+1, shapes[(int)next[i]->shape]);
    }for (int i = 0; i < 15; i++){
        printf(" ");
    }
    printf("\xb3\n");
    printf("\xb3");
    for (int i = 0; i < 34; i++){
        printf(" ");
    }
    printf("\x1e");
    for (int i = 0; i < 34; i++){
        printf(" ");
    }
    printf("\xb3\n");
    printf("\xc3");
    for (int i = 0; i < 69; i++){
        printf("\xc4");
    }
    printf("\xb4\n");
    printf("\x1b[0m\n");
    printf("\n");
}

#else

void printState(Liste * mainlist, int score, Piece ** next){
    char shapes[] = "TRCL";
    printf("\033[2J\033[0;0H\u250c");
    for (int i = 0; i < 69; i++){
        printf("\u2500");
    }
    printf("\u2510\n\u2502");
    for (int i = 0; i < 31; i++){
        printf(" ");
    }
    printf("Score : %d", score);
    for (int i = 0; i< 30-max((floor(log10(score))+1), 1); i++){
        printf(" ");
    }
    printf("\u2502\n\u251c");
    for (int i = 0; i < 69; i++){
        printf("\u2500");
    }
    printf("\u253c");
    for (int i = 0; i<19; i++){
        printf("\u2500");
    }
    printf("\u2510\n\u2502");
    for (int i = 0; i<69; i++){
        printf(" ");
    }
    printf("\u2502 Keybinds :        \u2502\n\u2502");
    for (int i = 0; i<69; i++){
        printf(" ");
    }
    printf("\u2502 g - Insert left   \u2502\n\u2502");
    for (int i = 0; i < 35-mainlist->length; i++){
        printf(" ");
    }
    printList(mainlist);
    for (int i = 0; i < 34-mainlist->length; i++){
        printf(" ");
    }
    printf("\u2502 d - Insert right  \u2502\n\u2502");
    for (int i = 0; i<69; i++){
        printf(" ");
    }
    printf("\u2502 c - Rotate colors \u2502\n\u2502");
    for (int i = 0; i<69; i++){
        printf(" ");
    }
    printf("\u2502 f - Rotate shapes \u2502\n");

    printf("\u251c");
    for (int i = 0; i < 69; i++){
        printf("\u2500");
    }
    printf("\u253c");
    for (int i = 0; i<19; i++){
        printf("\u2500");
    }
    printf("\u2518\n\u2502");
    for (int i = 0; i < 34; i++){
        printf(" ");
    }
    printf("\u25BC");
    for (int i = 0; i < 34; i++){
        printf(" ");
    }
    printf("\u2502\n\u2502");
    for (int i = 0; i < 32; i++){
        printf(" ");
    }
    printf("\u25B6 \033[3%dm%c\x1b[0m \u25C0  Next : \x1b[0m", next[0]->col+1, shapes[(int)next[0]->shape]);
    for (int i = 1; i<5; i++){
        printf("\033[3%dm%c\x1b[0m ", next[i]->col+1, shapes[(int)next[i]->shape]);
    }
    for (int i = 0; i < 15; i++){
        printf(" ");
    }
    printf("\u2502\n\u2502");
    for (int i = 0; i < 34; i++){
        printf(" ");
    }
    printf("\u25B2");
    for (int i = 0; i < 34; i++){
        printf(" ");
    }
    printf("\u2502\n\u2514");
    for (int i = 0; i < 69; i++){
        printf("\u2500");
    }
    printf("\u2518\n");
}

#endif

Piece * getRandPiece(int n_shapes, int n_colors){
    // Get a Piece with a random shape and color
    Piece * f = malloc(sizeof(Piece));

    f->col = rand()%n_colors;
    f->shape = rand()%n_shapes;
    return f;
}

Liste * getList(void){
    // Get empty Liste
    Liste * l = malloc(sizeof(Liste));
    l->length = 0;
    l->first = NULL;
    return l;
}

void appendListeID(Liste * l, Piece * f, int mainID){
    // Insert Piece in Liste according to the mainID provided
    Maillon * m = malloc(sizeof(Maillon));
    m->f = f;
    m->mainID = mainID;
    if (l->length == 0){
        l->first = m;
        m->next = m;
        m->prev = m;
        l->length++;
        return;
    }
    if (l->first->mainID > mainID){
        m->next = l->first;
        m->prev = l->first->prev;
        l->first->prev->next = m;
        l->first->prev = m;
        l->first = m;
        l->length++;
        return;
    }
    Maillon * iter = l->first;
    for (int i = 0; i<l->length-1; i++){
        if (iter->next->mainID > mainID){
            m->next = iter->next;
            m->prev = iter;
            iter->next->prev = m;
            iter->next = m;
            l->length++;
            return;
        }
        iter = iter->next;
    }
    m->next = iter->next;
    m->prev = iter;
    iter->next->prev = m;
    iter->next = m;
    l->length++;
    return;
}

void appendListe(Liste * l, Piece * f, char pos){
    // Create a new Maillon pointing to a given Piece and append it to the beginning or the end of a given Liste
    Maillon * m = malloc(sizeof(Maillon));
    m->f = f;
    if (l->length == 0){
        l->first = m;
        m->next = m;
        m->prev = m;
        m->mainID = 0;
        l->length++;
        return;
    }
    m->next = l->first;
    m->prev = l->first->prev;
    l->first->prev->next = m;
    l->first->prev = m;
    if (pos == 0){
        l->first = m;
        m->mainID = m->next->mainID-1;
    } else {
        m->mainID = m->prev->mainID+1;
    }
    l->length++;
    return;
}

void remListe(Liste * l, Piece * rem){
    // Remove any Maillon pointing to a given Piece from a given Liste
    if (l->length == 0){
        return;
    }
    
    Maillon * m = l->first;
    if (m->f == rem){
        if (l->length == 1){
            l->first = NULL;
            l->length -= 1;
            free(m);
            return;
        }
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

    if (l->length == 0){
        l->first = NULL;
    }
}

void clearList(Liste * l){
    if (l->length == 0){
        return;
    }
    Maillon * m = l->first;
    Maillon * next;
    for (int i = 0; i<l->length-1; i++){
        next = m->next;
        free(m);
        m = next;
    }
    free(m);
    l->length = 0;
    l->first = NULL;
}

void rotateMlist(Liste * mainlist, Liste * rot, Liste ** collist, Liste ** shaplist){
    // doesn't work for some reason
    if (rot->length <= 1){
        return;
    }
    Maillon * iter = rot->first;
    Maillon * m = mainlist->first;
    for (int i = 0; i<rot->length;i++){
        printf("/%d\\", i);
        while (m->f != iter->f){
            // printf(" l ");
            m = m->next;
            printf("loop : %p\n", m);
        }

        printf("|%d|", i);
        printf("m->f:%p iter->f:%p m:%p - ", m->f, iter->f, m);
        m->f = iter->next->f;
        printf("m->f:%p iter->next->f%p m:%p\n", m->f, iter->next->f, m);

        if (rot->type == 0){
            // printf("av ");
            remListe(shaplist[(int)m->f->shape], m->f);
            // printf("ap ");
            appendListeID(shaplist[(int)m->f->shape], m->f, m->mainID);
            // printf("ad ");
        } else {
            // printf("av ");
            remListe(collist[(int)m->f->col], m->f);
            // printf("ap ");
            appendListeID(collist[(int)m->f->col], m->f, m->mainID);
            // printf("ad ");
        }
        iter = iter->next;
        m = m->next;
    }
    rot->first = rot->first->next;
}

void rotateMList4(Liste * mainlist, Liste * rot, Liste ** collist, Liste ** shaplist, int n_col, int n_shap){
    if (rot->length <= 1){
        return;
    }
    Maillon * iter = rot->first;
    Maillon * m = mainlist->first;
    for (int i = 0; i<rot->length;i++){
        while (m->f != iter->f){
            m = m->next;
        }

        // printf("m->f:%p iter->f:%p m:%p - ", m->f, iter->f, m);
        m->f = iter->next->f;
        // printf("m->f:%p iter->next->f%p m:%p\n", m->f, iter->next->f, m);

        iter = iter->next;
        m = m->next;
    }
    // printf("éo");
    for (int i = 0; i < n_col; i++){
        clearList(collist[i]);
    }
    for (int i = 0; i < n_shap; i++){
        clearList(shaplist[i]);
    }
    // printf("éa");
    m = mainlist->first;
    for (int i = 0; i < mainlist->length; i++){
        appendListe(collist[(int)m->f->col], m->f, 1);
        appendListe(shaplist[(int)m->f->shape], m->f, 1);
        m = m->next;
    }
}

int checkListe(Liste * l, Piece ** ID){
    if (l->length == 0){
        return 0;
    }

    int simC = 1;
    int simT = 1;
    char prevC = -1;
    char prevT = -1;

    Maillon * m = l->first;

    for(int i = 0; i<l->length; i++){

        if (m->f->col == prevC){
            simC++;
        } else if (simC >= 3){
            return simC;
        } else {
            simC = 1;
            prevC = m->f->col;
        }

        if (m->f->shape == prevT){
            simT++;
        } else if (simT >= 3) {
            return simT;
        } else {
            simT = 1;
            prevT = m->f->shape;
        }

        for (int i = 0; i<4; i++){
            ID[4-i] = ID[3-i];
        }
        ID[0] = m->f;

        m = m->next;
    }

    if (simC >= 3 || simT >= 3){
        return max(simC, simT);
    }
    return 0;
}

void freeMainListe(Liste* l) {
    // Free each Maillon of a given Liste (circular)
    Maillon *m = l->first;
    Maillon *next;
    for (int i = 0; i<l->length-1; i++) {
        next = m->next;
        free(m->f);
        free(m);
        m = next;
    }
    free(m);
    free(l);
}

void freeListe(Liste* l) {
    // Free each Maillon of a given Liste (circular)
    Maillon *m = l->first;
    Maillon *next;
    for (int i = 0; i < l->length-1; i++) {
        next = m->next;
        free(m);
        m = next;
    }
    free(m);
    free(l);
}

void savegame(Liste * mainlist, Piece ** next, int score, int n_col, int n_shap, int max_piece){
    FILE * f = fopen("save.txt", "w");
    fprintf(f, "%d %d %d %d ", score, max_piece, n_col, n_shap);
    for (int i = 0; i < 5; i++){
        fprintf(f, "%d ", next[i]->col*n_shap+next[i]->shape);
    }
    Maillon * m = mainlist->first;
    for (int i = 0; i<mainlist->length; i++){
        fprintf(f, "%d ", m->f->col*n_shap+m->f->shape);
        m = m->next;
    }
    fclose(f);
}

void loadgame(Liste * mainlist, Piece ** next, int * score, int * n_col, int * n_shap, int * max_piece){
    FILE * f = fopen("save.txt", "r");
    char line[70];
    fgets(line, 70, f);
    char * p_save = strtok(line, " ");
    *score = atoi(p_save);
    p_save = strtok(NULL, " ");
    *max_piece = atoi(p_save);
    p_save = strtok(NULL, " ");
    *n_col = atoi(p_save);
    p_save = strtok(NULL, " ");
    *n_shap = atoi(p_save);
    Piece * p;
    int p_id;
    for (int i = 0; i < 5; i++){
        p_save = strtok(NULL, " ");
        printf("%s ", p_save);
        p = malloc(sizeof(Piece));
        p_id = atoi(p_save);
        p->shape = p_id%(*n_shap);
        p->col = p_id/(*n_shap);
        next[i] = p;
    }
    p_save = strtok(NULL, " ");
    while (p_save != NULL){
        printf("%s ", p_save);
        p = malloc(sizeof(Piece));
        p_id = atoi(p_save);
        p->shape = p_id%(*n_shap);
        p->col = p_id/(*n_shap);
        appendListe(mainlist, p, 1);
        p_save = strtok(NULL, " ");
    }
    fclose(f);
}

//
//
// SDL FUNCTIONS
//
//

char * intToString(int n){
    if (n == 0){
        return "0";
    }
    int size = floor(log10(n))+1;
    char * res = malloc(size+1);
    for (int i = 0; i<size; i++){
        res[size-i-1] = (char)(n%10)+'0';
        n/= 10;
    }
    res[size] = '\0';
    return res;
}

char * scoreString(int n){
    if (n == 0){
        return "Score : 0";
    }
    int size = 8+floor(log10(n))+1;
    char * res = malloc(size+1);
    strcpy(res, "Score : ");
    char * strAAAAA = intToString(n);
    strcat(res, strAAAAA);
    free(strAAAAA);
    res[size] = '\0';
    return res;
}

char * shapeString(int n){
    if (n == 0){
        return "Shapes : 0";
    }
    int size = 9+floor(log10(n))+1;
    char * res = malloc(size+1);
    strcpy(res, "Shapes : ");
    char * strAAAAA = intToString(n);
    strcat(res, strAAAAA);
    free(strAAAAA);
    res[size] = '\0';
    return res;
}

void colorFromNumber(int n, int * r, int * g, int * b){
    // 0 <= n <= 6*256-1, puts associated color in r g and b, each color has max saturation of the corresponding hue.
    switch (n/256){
        case 0:
            *r=255;
            *g=n%256;
            *b = 0;
            break;
        case 1:
            *g = 255;
            *r = 255-(n%256);
            *b = 0;
            break;
        case 2:
            *g = 255;
            *b = n%256;
            *r = 0;
            break;
        case 3:
            *b = 255;
            *g = 255-(n%256);
            *r = 0;
            break;
        case 4:
            *b = 255;
            *r = n%256;
            *g = 0;
            break;
        case 5:
            *r = 255;
            *b = 255-(n%256);
            *g = 0;
            break;
    }
}

void rota(double * x, double * y, double angle){
    // Rotate x and y coordinate of an angle around the origin
    double nx = (*x)*cos(angle) - (*y)*sin(angle);
    double ny = (*x)*sin(angle) + (*y)*cos(angle);
    *x = nx;
    *y = ny;
}

void aathickLineRGBA(SDL_Renderer * rend, int x1, int y1, int x2, int y2, int thickness, int r, int g, int b, int a){
    // Draw a thick line with anti aliasing

    // Compute line vector coordinates
    double vectx = x1 - x2;
    double vecty = y1 - y2;

    // Convert to a normalized orthogonal vector
    rota(&vectx, &vecty, pi/2);
    double norm = sqrt(vectx*vectx + vecty*vecty);
    vectx /= norm;
    vecty /= norm;

    short * x = malloc(sizeof(short)*4);
    short * y = malloc(sizeof(short)*4);

    // Compute the 4 verteces of the thick line
    x[0] = (short) x1 - vectx*thickness/2;
    x[1] = (short) x2 - vectx*thickness/2;
    x[2] = (short) x2 + vectx*thickness/2;
    x[3] = (short) x1 + vectx*thickness/2;

    y[0] = (short) y1 - vecty*thickness/2;
    y[1] = (short) y2 - vecty*thickness/2;
    y[2] = (short) y2 + vecty*thickness/2;
    y[3] = (short) y1 + vecty*thickness/2;

    // Draw an anti aliased empty polygon then fill it with a normal tick line
    thickLineRGBA(rend, x1, y1, x2, y2, thickness, r, g, b, a);
    aapolygonRGBA(rend, x, y, 4, r, g, b, a);

    free(x);
    free(y);
}

void drawpoly(SDL_Renderer * rend, int sides, int x, int y, int size, int r, int g, int b){
    // Draw a regular polygon with a given number of sides using rotations (very cool !)
    double angle = 2*pi/sides;
    double absx1 = 0.0, absy1 = -1.0; // first vertex of the polygon
    double absx2 = 0.0, absy2 = -1.0; // second vertex of the polygon
    rota(&absx2, &absy2, angle); // rotate the second vertex to it's right position
    for (int i = 0; i<sides; i++){
        // draw line between the two verteces
        aathickLineRGBA(rend, x+absx1*(size/2), y+absy1*(size/2), x+absx2*(size/2), y+absy2*(size/2), size/5, r, g, b, 255);
        // draw circle on vertex for round edges
        aacircleRGBA(rend, x+absx1*(size/2), y+absy1*(size/2), size/10, r, g, b, 255);
        filledCircleRGBA(rend, x+absx1*(size/2), y+absy1*(size/2), size/10, r, g, b, 255);
        // rotate the old verteces to new verteces
        absx1 = absx2;
        absy1 = absy2;
        rota(&absx2, &absy2, angle);
    }
}

void draw_edges_number(SDL_Renderer * rend, TTF_Font * font, int n, int x, int y){
    SDL_Color white = {255, 255, 255};
    char * n_str = intToString(n);
    SDL_Surface * txt_n = TTF_RenderText_Solid(font, n_str, white);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(rend, txt_n);
    SDL_Rect Rect = {x-txt_n->w/2, y-txt_n->h/2, txt_n->w, txt_n->h};
    SDL_FreeSurface(txt_n);

    SDL_RenderCopy(rend, tex, NULL, &Rect);
    SDL_DestroyTexture(tex);
}

int ButtonClick(SDL_Event * event, SDL_Rect * rect){
    return event->button.y >= rect->y && event->button.y <= rect->y+rect->h && event->button.x >= rect->x && event->button.x <= rect->x+rect->w;
}

SDL_Texture * getTexFromImg(SDL_Renderer * rend, char * imgname){
    SDL_Surface * sur = IMG_Load(imgname);
    if (!sur){
        printf("Error loading %s", imgname);
    }
    SDL_Texture * res = SDL_CreateTextureFromSurface(rend, sur);
    SDL_FreeSurface(sur);
    return res;
}

void SDL_RenderDrawText(SDL_Renderer * rend, TTF_Font * font, int x, int y, char * text){
    SDL_Color white = {255, 255, 255};
    SDL_Rect rect;
    SDL_Surface * txt = TTF_RenderText_Solid(font, text, white);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(rend, txt);
    rect.w = txt->w;
    rect.h = txt->h;
    SDL_FreeSurface(txt);
    rect.x = x;
    rect.y = y;
    SDL_RenderCopy(rend, tex, NULL, &rect);
}

int loadscore(int scores[10], char * initiales[4]){
    FILE * f = fopen("score.txt", "w");
    for (int i = 0; i<10; i++){
        fprintf(f, "%d %s\n", scores[i], initiales[i]);
    }
    fclose(f);
    return 0;
}

int getScores(int scores[10], char * initiales[4]){
    FILE * f = fopen("score.txt", "r");
    char buffer[10];
    int line = 0;
    while (fgets(buffer, 10, f)){
        int i = 0;
        scores[line] = 0;
        for (; buffer[i] != ' '; i++){
            scores[line] *= 10;
            scores[line] += buffer[i]-'0';
        }
        i++;
        for (int j = 0; j < 3; j++){
            initiales[line][j] = buffer[i+j];
        }
        initiales[line][3] = 0;
        line++;
    }
    return line;
}