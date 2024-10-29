#include "position.h"

Position::Position(int x, int y): x(x), y(y) {}

Position::Position(): x(0), y(0) {}

bool Position::operator==(const Position& other) const { return (x == other.x && y == other.y); }

Position Position::operator=(const Position& other) {
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

bool Position::operator<(const Position& other) const{
    int abs_this , abs_other;
    if (this == &other) return false;
    abs_this = std::abs(this->x) + std::abs(this->y);
    abs_other = std::abs(other.x) + std::abs(other.y);
    return abs_this < abs_other;
}

bool Position::operator>(const Position& other) const{
    int abs_this , abs_other;
    if (this == &other) return false;
    abs_this = std::abs(this->x) + std::abs(this->y);
    abs_other = std::abs(other.x) + std::abs(other.y);
    return abs_this > abs_other;
}

bool Position::operator<=(const Position& other) const{
    int abs_this , abs_other;
    if (this == &other) return true;
    abs_this = std::abs(this->x) + std::abs(this->y);
    abs_other = std::abs(other.x) + std::abs(other.y);
    return abs_this <= abs_other;
}

bool Position::operator>=(const Position& other) const{
    int abs_this , abs_other;
    if (this == &other) return true;
    abs_this = std::abs(this->x) + std::abs(this->y);
    abs_other = std::abs(other.x) + std::abs(other.y);
    return abs_this >= abs_other;
}
// implementar destructor
Position::~Position() {}
