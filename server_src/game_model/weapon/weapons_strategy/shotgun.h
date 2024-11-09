#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "weapon_interface.h"
#include "../bullets_strategy/pellet.h"
#include "../bullets_strategy/bullet_interface.h"

#define TILES_PELLET_DISTANCE 100

// class Shotgun : public WeaponInterface{
//     private:

//     public:
//          // std::vector<BulletInterface> fire(Position start_position, Position direction){
//          //    std::vector<BulletInterface> bullets;
//          //    bullets.push_back(Pellet(start_position, direction, TILES_PELLET_DISTANCE));
//          //    bullets.push_back(Pellet(start_position, direction + Position(1,0), TILES_PELLET_DISTANCE));
//          //    bullets.push_back(Pellet(start_position, direction + Position(-1,0), TILES_PELLET_DISTANCE));
//          //    bullets.push_back(Pellet(start_position, direction + Position(-2,0), TILES_PELLET_DISTANCE));
//          //    bullets.push_back(Pellet(start_position, direction + Position(2,0), TILES_PELLET_DISTANCE));
//          //    bullets.push_back(Pellet(start_position, direction + Position(-3,0), TILES_PELLET_DISTANCE));
//          // }
// };

#endif
