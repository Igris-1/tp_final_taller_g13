#include "duck.h"
#include <sstream>

Duck::Duck(int duck_id, int x, int y): duck_id(duck_id), pos({x, y}) {}

void Duck::move(int x, int y){
    pos.x += x;
    pos.y += y;
}

Position Duck::get_pos(){
    return pos;
}

std::string Duck::serialize() {
    std::ostringstream oss;
    oss << duck_id << " " << pos.x << " " << pos.y;
    return oss.str();
}

Duck Duck::deserialize(std::string& data) {
    std::istringstream iss(data);
    int id;
    float x, y;
    iss >> id >> x >> y;
    return Duck(id, x, y);
}
