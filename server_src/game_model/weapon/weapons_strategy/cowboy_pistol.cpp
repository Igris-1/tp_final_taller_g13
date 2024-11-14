#include "cowboy_pistol.h"
#include "../../duck.h"

std::vector<std::shared_ptr<BulletInterface>> CowboyPistol::fire(std::shared_ptr<Duck> duck_trigger, int x_position, int y_position, int x_direction, int y_direction){
   std::vector<std::shared_ptr<BulletInterface>>  bullets;
   if(this->ammo == 0){
      return bullets;
   }
   if(this->fire_rate == 0){
      bullets.push_back(std::make_shared<Bullet>(duck_trigger->get_id(), x_position, y_position, x_direction, y_direction));
      ammo--;
      this->fire_rate = FIRE_RATE_COWBOY_PISTOL;
   }
   return bullets;
}

int CowboyPistol::get_id(){
   return COWBOY_PISTOL_ID;
}

int CowboyPistol::recoil_produced(){
   return COWBOY_PISTOL_RECOIL;
}