#ifndef HITBOX_H
#define HITBOX_H

#include <iostream>
#include <set>
#include <list>

class Hitbox {
private:
    /*
        X e Y es el punto de arriba a la izquierda. ya que sdl usa ese sistema de coordenadas
    */
    int x;
    int y;
    int width;
    int height;
    int original_DY;

public:
    Hitbox(int x, int y, int width, int height);

    bool has_collision(const int x, const int y);

    bool has_collision(const Hitbox& other) const;

    bool has_collision_above(const Hitbox& other) const;

    Hitbox& operator=(const Hitbox& other);

    bool operator==(const Hitbox& other) const;

    bool operator<(const Hitbox& other) const;

    bool operator>(const Hitbox& other) const;

    bool operator<=(const Hitbox& other) const;

    bool operator>=(const Hitbox& other) const;

    void move_relative(int x, int y);

    void move(int x, int y);

    int get_x() const;
    int get_y() const;
    int get_width();
    int get_height();

    bool change_size(int new_width, int new_height, 
        const std::set<Hitbox>& potential_collisions, std::list<Hitbox>& boxes);
};

#endif
