/*#pragma once

#include <vector>
#include <string>

struct image_position {
    int x;
    int y;

    image_position(int x, int y) : x(x), y(y) {}
} ;

struct SimpleDuck{
    image_position pos;
    SimpleDuck(image_position position) : pos(position) {}
};

struct Snapshot{
    std::vector<SimpleDuck> ducks;
    //std::vector<bullets> boxes;
    //std::vector<items> bullets;
};


class GameSnapshot {
    private:
        Snapshot snapshot_data;

    public:
        GameSnapshot* clone();
        Snapshot get_snapshot();
        void add_duck(SimpleDuck duck);
        SimpleDuck get_duck();
        std::string serialize();
        //GameSnapshot deserialize(std::string& data);
};*/
