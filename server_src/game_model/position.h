#ifndef POSITION_H
#define POSITION_H

class Position {
private:
    // cppcheck-suppress unusedStructMember
    int x;
    // cppcheck-suppress unusedStructMember
    int y;

public:
    Position(int x, int y);

    bool operator==(const Position& other) const;
    Position& operator=(const Position& other);
    Position& operator+(const Position& other) const;
    int get_x();
    int get_y();
    ~Position();
};

#endif
