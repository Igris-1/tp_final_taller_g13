#pragma once
#include <string>
#include "../common_src/game_snapshot.h"

class Duck {

    private:
        int duck_id;
        Position pos;

    public:
        Duck(int duck_id, int x, int y);

        void move(int x, int y);
        Position get_pos();

        //std::string serialize();

        //Duck deserialize(std::string& data);

};
