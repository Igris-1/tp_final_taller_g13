#pragma once

class Position{
    private:
        int x;
        int y;
    public:
        Position(int x, int y);
        bool operator==(const Position& other) const;
        Position& Position::operator=(const Position& other);
        //int get_x();
        //int get_y();
        ~Position();
};