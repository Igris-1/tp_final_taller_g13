#include "position.h"

Position::Position(int x, int y): x(x), y(y) {}

Position::Position(): x(0), y(0) {}

bool Position::operator==(const Position& other) const {
     return (x == other.x && y == other.y); }

Position& Position::operator=(const Position& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

int Position::get_x() { return x; }

int Position::get_y() { return y; }

Position Position::operator+(const Position& other) const {
    Position newPosition(this->x + other.x, this->y + other.y);
    return newPosition;
}

bool Position::operator<(const Position& other) const {
    if (this->x == other.x) {
        return this->y < other.y;
    }
    return this->x < other.x;
}

bool Position::operator>(const Position& other) const {
    if (this->x == other.x) {
        return this->y > other.y;
    }
    return this->x > other.x;
}

bool Position::operator<=(const Position& other) const {
    return !(*this > other);
}

bool Position::operator>=(const Position& other) const {
    return !(*this < other);
}
Position::~Position() {}
