#pragma once

#include <vector>
#include "../server_src/duck.h"

typedef struct {
    std::vector<Duck> ducks;
} snapshot;

class GameSnapshot {
    private:
        snapshot snapshot_data;

    public:
        GameSnapshot* clone();
        snapshot get_snapshot();
        void add_duck(Duck duck);
        Duck get_duck();
        std::string serialize();
        GameSnapshot deserialize(std::string& data);
};
