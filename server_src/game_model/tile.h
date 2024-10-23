#pragma once
#include <vector>

class Tile{
    private:
    //Position position; ??
    std::vector<int> gameObject;
    public:
    Tile();
    void add_game_object(int object);
};