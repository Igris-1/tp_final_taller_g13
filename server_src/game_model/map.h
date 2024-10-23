#pragma once

#include "tile.h"
class Map {
    private:
        int width;
        int height;
        Tile* matrix;
    public:
        Map(int width, int height);
        ~Map();
        void add_game_object(int x, int y, int object);
};
