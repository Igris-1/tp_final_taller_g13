#pragma once

#include <vector>
#include <string>

struct Position {
    int x;
    int y;

    Position(int x, int y) : x(x), y(y) {}
} ;

struct SimpleDuck{
    Position pos;

    SimpleDuck(Position position) : pos(position) {}
};

struct Snapshot{
    std::vector<SimpleDuck> ducks;
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
};
