#include "hitbox.h"

Hitbox::Hitbox(int x, int y, int width, int height): x(x), y(y), width(width), height(height) {
        this->original_DY = height - y;
    };

bool Hitbox::has_collision(const int x, const int y) {
    return (x >= this->x && x <= this->x + this->width && y >= this->y &&
            y <= this->y + this->height);
}

bool Hitbox::has_collision(const Hitbox& other) const {
    return (this->x<other.x + other.width&& this->x + this->width> other.x) &&
            (this->y<other.y + other.height&& this->y + this->height> other.y);
}

bool Hitbox::has_collision_above(const Hitbox& other) const {
    return (this->y<other.y + other.height&& this->y + this->height> other.y);
}

Hitbox& Hitbox::operator=(const Hitbox& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
    }
    return *this;
}

bool Hitbox::operator==(const Hitbox& other) const {
    return (x == other.x && y == other.y && width == other.width && height == other.height);
}

bool Hitbox::operator<(const Hitbox& other) const {
    if (x != other.x)
        return x < other.x;
    if (y != other.y)
        return y < other.y;
    if (width != other.width)
        return width < other.width;
    return height < other.height;
}

bool Hitbox::operator>(const Hitbox& other) const { return other < *this; }

bool Hitbox::operator<=(const Hitbox& other) const { return !(other < *this); }

bool Hitbox::operator>=(const Hitbox& other) const { return !(*this < other); }

void Hitbox::move_relative(int x, int y) {
    this->x += x;
    this->y += y;
}

void Hitbox::move(int x, int y) {
    this->x = x;
    this->y = y;
}

int Hitbox::get_x() const { return this->x; }
int Hitbox::get_y() const { return this->y; }
int Hitbox::get_width() { return this->width; }
int Hitbox::get_height() { return this->height; }

bool Hitbox::change_size(int new_width, int new_height, const std::set<Hitbox>& potential_collisions, std::list<Hitbox>& boxes) {
    if (new_height > this->height) {
        int height_difference = new_height - this->height;
        int new_y = this->y - height_difference;

        Hitbox new_hitbox = *this;
        new_hitbox.y = new_y;
        new_hitbox.height = new_height;

        for (const Hitbox& other: potential_collisions) {
            if (new_hitbox.has_collision(other)) {
                return false;
            }
        }
        for (const Hitbox& other2: boxes) {
            if (new_hitbox.has_collision(other2)) {
                return false;
            }
        }
        this->y = new_y;
    }
    this->width = new_width;
    this->height = new_height;
    return true;
}