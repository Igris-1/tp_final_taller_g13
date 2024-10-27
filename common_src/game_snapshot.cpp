/*#include "game_snapshot.h"
#include <sstream>

GameSnapshot* GameSnapshot::clone() {
    return new GameSnapshot();
}

Snapshot GameSnapshot::get_snapshot() {
    return snapshot_data;
}

void GameSnapshot::add_duck(SimpleDuck duck) {
    snapshot_data.ducks.push_back(duck);
}

SimpleDuck GameSnapshot::get_duck() {
    return snapshot_data.ducks.at(0);
}

std::string GameSnapshot::serialize(){
    std::ostringstream oss;
    oss << snapshot_data.ducks.size() << " ";
    SimpleDuck duck = get_duck();
    oss << duck.pos.x << " " << duck.pos.y << " ";
    return oss.str();
}

/*GameSnapshot GameSnapshot::deserialize(std::string& data) {
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
}*/
