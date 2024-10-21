#pragma once
#include "../../common_src/game_snapshot.h"

class Duck {

    private:
        int duck_id;
        Position pos;

    public:
        Duck(int duck_id, float x, float y);
        
        int get_duck_id();
        Position get_pos();


        //indicar el sentido a moverse como versores con 'x' positivo hacia la derecha
        // e 'y' positivo hacia arriba 
        // (0, 1) arriba 
        // (0, -1)  abajo
        // (1, 0)  derecha
        // (-1, 0) izq
        // no le mandes cualquier cosa a este metodo, mandale solo (1,0) (0,1) (-1,0) o (0,-1)
        void move(int x, int y);

        // void action();
        // void throw_equipment();

        ~Duck();

};