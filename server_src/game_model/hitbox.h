#ifndef HITBOX_H
#define HITBOX_H

class Hitbox {
    private:
        /*
            X e Y es el punto de arriba a la izquierda. ya que sdl usa ese sistema de coordenadas
        */
        int x;
        int y;
        int width;
        int height;
    public:
    Hitbox(int x, int y, int width, int height): x(x), y(y), width(width), height(height) {};

    bool has_collision(const int x, const int y) {
        return (x >=this->x && x <= this->x + this->width && y >= this->y && y <= this->y + this->height);
    }
    bool has_collision(const Hitbox& other){
        return  (this->x < other.x + other.width && this->x + this->width > other.x) &&
                (this->y < other.y + other.height && this->y + this->height > other.y);
        // deberian ser <= y >=   ???
    }
    int get_x() { return this->x; }
    int get_y() { return this->y; }
    int get_width() { return this->width; }
    int get_height() { return this->height; }
};

#endif
