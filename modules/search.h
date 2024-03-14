#pragma once
#include "utils.h"

int evaluate(Liste * mainlist){
    if (mainlist->length == 0){
        
    }
    int res = -2*mainlist->length;
    
}

typedef struct node {
    // Current score
    char score;

    // Pointers to Lists with current state
    Liste * mainlist;
    Liste ** colList;
    Liste ** shapList;

    // Pointers to nodes after a certain action
    struct node * left;
    struct node * right;
    struct node ** colRot;
    struct node ** shapRot;
} Node;