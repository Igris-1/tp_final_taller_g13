#pragma once
#include "Duck.h"

Duck::Duck(int duck_id, float x, float y): duck_id(duck_id), pos({x, y}) {}

// no le mandes cualquier cosa
// a este metodo, mandale solo (1,0) (0,1) (-1,0) o (0,-1)
void Duck::move(int x, int y){

    if(x == 1 && y == 0){
        this->pos.x += 1;
        return;
    }
    if(x == -1 && y == 0){
        this->pos.x -= 1;
        return;
    }
    if(x == 0 && y == 1){
        this->pos.y += 1;
        return;
    }
    if(x == 0 && y == -1){
        this->pos.y -= 1;
        return;
    }
}