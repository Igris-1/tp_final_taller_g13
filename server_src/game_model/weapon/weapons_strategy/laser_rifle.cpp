#include "laser_rifle.h"

std::vector<std::shared_ptr<BulletInterface>> LaserRifle::fire(int duck_id, int x_position, int y_position, int x_direction, int y_direction){
   std::vector<std::shared_ptr<BulletInterface>> bullets;
   if(this->ammo == 0){
      return bullets;
   }
   if(this->fire_rate == 0){
      bullets.push_back(std::make_shared<Laser>(duck_id, x_position, y_position, x_direction, y_direction));
      ammo--;
      this->fire_rate = FIRE_RATE_LASER;
   }
   return bullets;
}

int LaserRifle::get_id(){
   return LASER_ID;
}