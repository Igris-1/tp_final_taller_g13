#include "pickable.h"

#include "duck.h"

void Pickable::air_time_down_y() {
        this->air_time_y--;
        if (air_time_y == 0) {
            falling = true;
        }
    }

void Pickable::air_time_down_x() {
        this->air_time_x--;
        if (air_time_x == 0) {
            moving = false;
        }
    }

bool Pickable::is_falling() { return falling; }
    
bool Pickable::is_moving() { return moving; }

void Pickable::set_falling(bool falling) { this->falling = falling; }

void Pickable::set_moving(bool moving) {
    this->moving = moving;
    if (moving) {
        this->air_time_x = 300;
    }
}

int Pickable::get_air_time_y() { return this->air_time_y; }

int Pickable::get_x_direction() { return this->x_direction; }

void Pickable::set_direction(int x, int y) {
    this->x_direction = x;
    this->y_direction = y;
    this->air_time_y = 50;
    this->air_time_x = 300;
}

void Pickable::add_owner(std::shared_ptr<Duck> new_duck) { this->duck = new_duck; }