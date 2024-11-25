#ifndef HITBOX_H
#define HITBOX_H

#include <set>
#include <iostream>

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
    Hitbox(int x, int y, int width, int height): x(x), y(y), width(width), height(height){
        this->original_DY = height-y;
    };

    bool has_collision(const int x, const int y) {
        return (x >= this->x && x <= this->x + this->width && y >= this->y &&
                y <= this->y + this->height);
    }
    bool has_collision(const Hitbox& other) const {
        return (this->x<other.x + other.width&& this->x + this->width> other.x) &&
               (this->y<other.y + other.height&& this->y + this->height> other.y);
    }

    bool has_collision_above(const Hitbox& other) const {
        // bool horizontal_overlap = (this->x < other.x + other.width) &&
        //                         (this->x + this->width > other.x);

        // bool above_overlap = (this->y > other.y + other.height) &&
        //                  (this->y - (this->height - other.height) <= other.y);

        // return horizontal_overlap && above_overlap;
        return (this->y<other.y + other.height&& this->y + this->height> other.y);
    }

    Hitbox& operator=(const Hitbox& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            width = other.width;
            height = other.height;
        }
        return *this;
    }
    bool operator==(const Hitbox& other) const {
        return (x == other.x && y == other.y && width == other.width && height == other.height);
    }

    bool operator<(const Hitbox& other) const {
        if (x != other.x)
            return x < other.x;
        if (y != other.y)
            return y < other.y;
        if (width != other.width)
            return width < other.width;
        return height < other.height;
    }

    bool operator>(const Hitbox& other) const { return other < *this; }

    bool operator<=(const Hitbox& other) const { return !(other < *this); }

    bool operator>=(const Hitbox& other) const { return !(*this < other); }
    void move_relative(int x, int y) {
        this->x += x;
        this->y += y;
    }
    void move(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int get_x() { return this->x; }
    int get_y() { return this->y; }
    int get_width() { return this->width; }
    int get_height() { return this->height; }

    // void change_size(int new_width, int new_height) {
    //     if (new_height > this->height) {
    //         int height_difference = new_height - this->height;
    //         this->y -= height_difference;
    //     }
    //     this->width = new_width;
    //     this->height = new_height;
    // }

    bool change_size(int new_width, int new_height, const std::set<Hitbox>& potential_collisions) {
        if (new_height > this->height) {
            // Calculate how much the hitbox would move upwards
            int height_difference = new_height - this->height;
            int new_y = this->y - height_difference;

            // Check for collisions with the new size
            Hitbox new_hitbox = *this;
            new_hitbox.y = new_y;
            new_hitbox.height = new_height;

            for (const Hitbox& other : potential_collisions) {
                if (new_hitbox.has_collision(other)) {
                    // Collision detected, cancel resizing
                    std::cout << "Collision detected above, resizing canceled!" << std::endl;
                    return false;
                }
            }

            // No collisions, apply the resize
            this->y = new_y;
        }

        // Update width and height
        this->width = new_width;
        this->height = new_height;
        return true;
    }

    
};

#endif
