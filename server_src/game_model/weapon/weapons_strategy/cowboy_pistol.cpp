#include "cowboy_pistol.h"

std::vector<std::shared_ptr<BulletInterface>> CowboyPistol::fire(int duck_id, int x_position, int y_position, int x_direction, int y_direction){
   std::vector<std::shared_ptr<BulletInterface>>  bullets;
   if(this->ammo == 0){
      return bullets;
   }
   if(this->fire_rate == 0){
      bullets.push_back(std::make_shared<Bullet>(duck_id, x_position, y_position, x_direction, y_direction));
      ammo--;
      this->fire_rate = FIRE_RATE_COWBOY;
   }
   return bullets;
}

int CowboyPistol::get_id(){
   return COWBOY_PISTOL_ID;
}
