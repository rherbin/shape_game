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

#define pi 3.1415926535897932384626433832795

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

//
//
// LIST MANAGEMENT FUNCTIONS
//
//

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
    // Print each Forme of a given Liste with ansi escape
    char types[] = "TRCL";
    if (l->length == 0){
        return;
    }
    Maillon * m = l->first;
    for (int i = 0; i<l->length; i++){
        printf("\033[3%dm%c%d\x1b[0m ", m->f->col+1, types[(int)m->f->type], m->f->mainID);
        m = m->next;
    }
}

void printMList(MListe * l){
    // Print each Forme of a given Liste with ansi escape
    char types[] = "TRCL";
    if (l->length == 0){
        return;
    }
    MaillonM * mm = l->first;
    for (int i = 0; i<l->length; i++){
        printf("\033[3%dm%c%d\x1b[0m ", mm->m->f->col+1, types[(int)mm->m->f->type], mm->m->f->mainID);
        mm = mm->next;
    }
}

void getForme(char type, char col, Forme * f){
    // Useless
    f->col = col;
    f->type = type;
    //return f;
}

Forme * getRandForme(int n_formes, int n_colors){
    // Get a Forme with a random type and color
    Forme * f = malloc(sizeof(Forme));

    getForme(rand()%n_formes, rand()%n_colors, f);
    return f;
}

Liste * getList(void){
    // Get empty Liste
    Liste * l = malloc(sizeof(Liste));
    l->length = 0;
    l->first = NULL;
    return l;
}

MListe * getMList(void){
    // Get empty Liste
    MListe * l = malloc(sizeof(MListe));
    l->length = 0;
    l->first = NULL;
    return l;
}

Maillon * appendListe(Liste * l, Forme * f, char pos){
    Maillon * m = malloc(sizeof(Maillon));
    m->f = f;
    if (l->length == 0){
        l->first = m;
        m->next = m;
        m->prev = m;
        l->length++;
        return m;
    }
    m->next = l->first;
    m->prev = l->first->prev;
    l->first->prev->next = m;
    l->first->prev = m;
    if (pos == 0){
        l->first = m;
    }
    l->length++;
    return m;
}

void appendMListe(MListe * l, Maillon * m, char pos){
    MaillonM * mm = malloc(sizeof(MaillonM));
    mm->m = m;
    if (l->length == 0){
        l->first = mm;
        mm->next = mm;
        mm->prev = mm;
        l->length++;
        return;
    }
    mm->next = l->first;
    mm->prev = l->first->prev;
    l->first->prev->next = mm;
    l->first->prev = mm;
    if (pos == 0){
        l->first = mm;
    }
    l->length++;
}

Maillon * appendMainListe(Liste * l, Forme * f, char pos){
    // Create a new Maillon pointing to a given Forme and append it to the beginning or the end of a given Liste
    Maillon * m = malloc(sizeof(Maillon));
    m->f = f;
    if (l->length == 0){
        l->first = m;
        m->next = m;
        m->prev = m;
        m->f->mainID = 0;
        l->length++;
        return m;
    }
    m->next = l->first;
    m->prev = l->first->prev;
    l->first->prev->next = m;
    l->first->prev = m;
    if (pos == 0){
        l->first = m;
        m->f->mainID = 0;
        for (int i = 0; i < l->length; i++){
            m = m->next;
            m->f->mainID++;
        }
    } else {
        m->f->mainID = m->prev->f->mainID+1;
    }
    l->length++;
    return m;
}

void appendListeWithID(Liste * l, Forme * f, char pos){
    // insert Maillon containing f in l, at the right position according to the mainID. 
    Maillon * iter = l->first;
    Maillon * m = malloc(sizeof(Maillon));
    m->f = f;
    // chek if insertion is first
    if (l->length == 0){
        l->first = m;
        m->next = m;
        m->prev = m;
        l->length++;
        return;
    }
    printf("ID1");
    if (f->mainID < l->first->f->mainID){
        m->next = l->first;
        l->first->prev->next = m;
        l->first->next->prev = m;
        m->prev = l->first->prev;
        l->first = m;
        l->length++;
        printf("ENDID1");
        return;
    }
    printf("ID2");
    // check for each element of liste
    for (int i = 0; i<l->length-1; i++){
        if (iter->next->f->mainID > f->mainID){
            iter->next->prev = m;
            m->next = iter->next;
            iter->next = m;
            m->prev = iter;
            l->length++;
            printf("ENDID2");
            return;
        }
    }
    // if no element is after, then it must be last
    printf("ID3");
    m->next = l->first;
    m->prev = l->first->prev;
    l->first->prev->next = m;
    l->first->prev = m;
    l->length++;
    printf("ID4");
}

void remMainListe(Liste * l, Forme * rem){
    if (l->length == 0){
        return;
    }

    Maillon * m = l->first;

    if (m->f == rem){
        l->first = l->first->next;
        l->length -= 1;
        return;
    }

    while (m != NULL && m->next != NULL){
        if (m->next->f == rem){
            m->next = m->next->next;
            l->length -= 1;
        }
        m = m->next;
    }
}

void remListe(Liste * l, Forme * rem){
    // Remove any Maillon pointing to a given Forme from a given Liste

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

    if (l->length == 0){
        l->first = NULL;
    }
}

void remMListe(MListe * l, Forme * rem){
    // Remove any Maillon pointing to a given Forme from a given Liste

    if (l->length == 0){
        return;
    }
    
    MaillonM * mm = l->first;
    if (mm->m->f == rem){
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

    mm = mm->next;
    for(int i = 0; i<l->length-1; i++){
        if (mm->m->f == rem){
            mm->prev->next = mm->next;
            mm->next->prev = mm->prev;
            //free(m);
            l->length -= 1;
            return;
        }
        mm = mm->next;
    }

    if (l->length == 0){
        l->first = NULL;
    }
}

void rotateMList(MListe * l, char type){
    // Rotate a given Liste around the color or the type

    if (l->length <= 1){
        return;
    }

    //printf("jahah");

    MaillonM * mm = l->first;
    Forme * tmp = mm->m->f;

    printf("lol");

    //printf("ici");

    for (int i = 0; i<l->length-1; i++){
        mm->m->f = mm->next->m->f;
        mm = mm->next;
    }

    //printf("la");

    mm->m->f = tmp;

    //l->first = l->first->next;
}

void rotateList(Liste * l, char type){
    // Rotate a given Liste around the color or the type

    if (l->length <= 1){
        return;
    }

    //printf("jahah");

    Maillon * m = l->first;
    char tmp;
    printf("lol");
    if (type == 1){
        tmp = m->f->col;
    } else {
        tmp = m->f->type;
    }

    //printf("ici");

    for (int i = 0; i<l->length-1; i++){
        if (type == 1){
            m->f->col = m->next->f->col;
        } else {
            m->f->type = m->next->f->type;
        }
        m = m->next;
    }

    //printf("la");

    if (type == 1){
        m->f->col = tmp;
    } else {
        m->f->type = tmp;
    }
}

int checkListe2(Liste * l, Forme ** ID){
    // Check a given Liste for 3 or more following shapes with the same shape or color and puts them into the given ID array.
    // Returns number of consecutive shapes found

    int simC = 1;
    int simT = 1;
    char prevC = 0;
    char prevT = 0;
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

int checkListe(Liste * l, Forme ** ID){
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

        if (m->f->type == prevT){
            simT++;
        } else if (simT >= 3) {
            return simT;
        } else {
            simT = 1;
            prevT = m->f->type;
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



void freeListe(Liste* l){
    // Free each Maillon of a given Liste
    Maillon * m = l->first->next;
    for (int i = 0; i < l->length-1; i++){
        m = m->next;
        free(m->prev->f);
        free(m->prev);
    }
    free(l->first->f);
    free(l->first);
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
    int size = ceil(log10(n));
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
    int size = 8+ceil(log10(n));
    char * res = malloc(size+1);
    strcpy(res, "Score : ");
    char * strAAAAA = intToString(n);
    strcat(res, strAAAAA);
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