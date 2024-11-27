#include "grenade.h"

Grenade::Grenade(int width, int height) : Pickable(0, 0, width, height){}

void Grenade::use(MapGame& map){
    this->active = true;
}

int Grenade::get_id(){
    if(this->active){
        return ACTIVATED_GRENADE_ID;
    }
    return GRENADE_ID;
}

bool Grenade::is_explosive(){
    return true;
}
bool Grenade::is_active(){
    return this->active;   
}

bool Grenade::exploted(){
    return this->explosive_time <= 0;
}

weapon_DTO Grenade::to_DTO(){
    weapon_DTO dto;
    dto.x = this->hitbox.get_x();
    dto.y = this->hitbox.get_y();
    dto.width = this->hitbox.get_width();
    dto.height = this->hitbox.get_height();
    dto.weapon_id = this->get_id();
    return dto;
}

std::vector<std::shared_ptr<BulletInterface>> Grenade::get_explotion(Hitbox hitbox){
    std::cout << "Grenade explotion" << std::endl;
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    int x = hitbox.get_x() + hitbox.get_width() / 2;
    int y = hitbox.get_y();
    bullets.push_back(std::make_shared<Laser>(-1, x, y, 1, 0,
                                            TRAVEL_DISTANCE_GRENADE));
    bullets.push_back(std::make_shared<Laser>(-1, x, y, 0, 1,
                                            TRAVEL_DISTANCE_GRENADE));
    bullets.push_back(std::make_shared<Laser>(-1, x, y, 1, 1,
                                            TRAVEL_DISTANCE_GRENADE));
    bullets.push_back(std::make_shared<Laser>(-1, x, y, -1, 0,
                                            TRAVEL_DISTANCE_GRENADE));
    bullets.push_back(std::make_shared<Laser>(-1, x, y, 0, -1,
                                            TRAVEL_DISTANCE_GRENADE));
    bullets.push_back(std::make_shared<Laser>(-1, x, y, -1, -1,
                                            TRAVEL_DISTANCE_GRENADE));
    bullets.push_back(std::make_shared<Laser>(-1, x, y, 1, 0,
                                            TRAVEL_DISTANCE_GRENADE));
    bullets.push_back(std::make_shared<Laser>(-1, x, y, 0, 1,
                                            TRAVEL_DISTANCE_GRENADE));
    bullets.push_back(std::make_shared<Laser>(-1, x, y, 1, 1,
                                            TRAVEL_DISTANCE_GRENADE));
    bullets.push_back(std::make_shared<Laser>(-1, x, y, -1, 0,
                                            TRAVEL_DISTANCE_GRENADE));
    bullets.push_back(std::make_shared<Laser>(-1, x, y, 0, -1,
                                            TRAVEL_DISTANCE_GRENADE));
    bullets.push_back(std::make_shared<Laser>(-1, x, y, -1, -1,
                                            TRAVEL_DISTANCE_GRENADE));
    this->explotion_time--;                                            
    return bullets;
}

bool Grenade::is_exploding() {
    return this->explotion_time > 0;
}

void Grenade::fire_rate_down(){
    if(this->is_active()){
        std::cout << "Grenade fire rate down" << std::endl;
        this->explosive_time--;
    }
}