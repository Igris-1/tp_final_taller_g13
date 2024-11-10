#ifndef BULLET_H
#define BULLET_H

#include "bullet_interface.h"

class MapGame;

#define TILES_BULLETS 256

class Bullet : public BulletInterface{
    private:
        
    public:
        Bullet(int x, int y, int x_direction, int y_direction);
        bool next_position(MapGame& map) override;
};

#endif
