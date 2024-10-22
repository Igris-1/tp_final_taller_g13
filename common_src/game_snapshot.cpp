#include "game_snapshot.h"
#include <sstream>

GameSnapshot* GameSnapshot::clone() {
    return new GameSnapshot();
}

snapshot GameSnapshot::get_snapshot() {
    return snapshot_data;
}

void GameSnapshot::add_duck(Duck duck) {
    snapshot_data.ducks.push_back(duck);
}

Duck GameSnapshot::get_duck() {
    return snapshot_data.ducks.at(0);
}

std::string GameSnapshot::serialize() {
    std::ostringstream oss;
    oss << snapshot_data.ducks.size() << " ";
    for (Duck& duck : snapshot_data.ducks) {
        oss << duck.serialize() << " ";
    }
    return oss.str();
}

GameSnapshot GameSnapshot::deserialize(std::string& data) {
    std::istringstream iss(data);
    GameSnapshot game_snapshot;
    size_t duck_count;
    iss >> duck_count;

    for (size_t i = 0; i < duck_count; ++i) {
        float x, y;
        int id;
        iss >> id >> x >> y;
        game_snapshot.add_duck(Duck(id, x, y));
    }

    return game_snapshot;
}
