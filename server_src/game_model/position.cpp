#include "position.h"

Position::Position(int x, int y): x(x), y(y) {}

bool Position::operator==(const Position& other) const { return (x == other.x && y == other.y); }

Position& Position::operator=(const Position& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

Position& Position::operator+(const Position& other) const {
    Position newPosition(this->x + other.x, this->y + other.y);
    return newPosition;
}

// implementar destructor
Position::~Position() {}
