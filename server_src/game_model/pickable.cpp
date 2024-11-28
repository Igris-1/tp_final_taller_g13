#include "pickable.h"

#include "duck.h"

Pickable::Pickable(int x, int y, int width, int height): Positionable(x, y, width, height) {}
Pickable::Pickable(): Positionable() {}

void Pickable::air_time_down_y() {
    if (this->air_time_y > 0) {
        this->air_time_y--;
        if (air_time_y <= 0) {
            falling = true;
        }
    }
}

void Pickable::set_airtime_y(int airtime) {
    this->air_time_y = airtime;
}

void Pickable::air_time_down_x() {
    if (this->air_time_x > 0) {
        this->air_time_x--;
        if (air_time_x <= 0) {
            moving = false;
        }
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

void Pickable::fire_rate_down() { return; }

int Pickable::recoil_produced() { return 0; }

void Pickable::set_holding(bool is_holding) { return; }

bool Pickable::is_explosive(){
    return false;
}
bool Pickable::is_banana(){
    return false;
}
bool Pickable::is_active(){
    return false;
}
void Pickable::activation(){
    return;
}
bool Pickable::exploted(){
    return false;
}

bool Pickable::is_exploding(){
    return false;
}

std::vector<std::shared_ptr<BulletInterface>> Pickable::get_explotion(Hitbox hitbox){
    return std::vector<std::shared_ptr<BulletInterface>>();
}