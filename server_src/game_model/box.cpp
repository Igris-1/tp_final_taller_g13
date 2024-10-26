#include "box.h"

Box::Box(int id, int x, int y, Positionable reward): box_id(id), reward(reward), Positionable(x, y) {
    this->has_reward = true;
}
Box::Box(int id, int x, int y): box_id(id), reward(0), Positionable(x, y) {
    this->has_reward = false;
}