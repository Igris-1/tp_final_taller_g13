#include "game.h"

Game::Game(int height, int width): map(width, height), ducks_states(), ducks() {}

void Game::duck_exist(int id){
    if (this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id error");
    }
    return;
}

int Game::add_duck(int health, int id) {
    if (this->ducks.find(id) != this->ducks.end()){
        throw GameError("Duck id already exists");
    }
    std::shared_ptr<Duck> new_duck = std::make_shared<Duck>(health, id);
    this->ducks[id] = new_duck;
    ducks_states.emplace(id, std::make_shared<duck_state>());
    return id;
}

void Game::remove_duck(int id){
    this->duck_exist(id);
    this->ducks.erase(id);
    this->ducks_states.erase(id);
}


void Game::run_duck(int duck_id, bool left, bool right){
    this->duck_exist(duck_id);
    if(!this->ducks[duck_id]->is_alive()){
        return;
    }
    if(!this->ducks_states[duck_id]->is_moving_left){
        this->ducks_states[duck_id]->is_moving_left = left;
         
    }
    if(!this->ducks_states[duck_id]->is_moving_right){
        this->ducks_states[duck_id]->is_moving_right = right;    
    }
}


void Game::pick_up_item(int id, bool pick_up){
    this->duck_exist(id);
    if(pick_up){
        for (auto it = weapons_on_map.begin(); it != weapons_on_map.end();){
            if(ducks[id]->get_hitbox().has_collision((*it)->get_hitbox())){
                std::shared_ptr<Weapon> other_weapon = ducks[id]->take_weapon(*it);
                if(other_weapon != nullptr){
                    other_weapon->move_to((*it)->get_x(), (*it)->get_y());
                    weapons_on_map.push_back(other_weapon);
                }
                it = weapons_on_map.erase(it);
                break;
            }
            else{
                if(ducks[id]->has_weapon()){
                    std::shared_ptr<Weapon> weapon = ducks[id]->throw_weapon();
                    if(weapon == nullptr){
                    }else{
                        std::cout << "devolvio un arma" << std::endl;
                    }
                    weapon->move_to(ducks[id]->get_x(), ducks[id]->get_y());
                    if(ducks_states[id]->facing_direction){
                        std::cout << "tiro a la der" << std::endl;
                        weapon->set_direction(1, -1);
                    }else{
                        std::cout << "tiro a la izq" << std::endl;
                        weapon->set_direction(-1, -1);
                    }
                    weapons_on_map.push_back(weapon);
                    return;
                }
            }
            ++it;
        }
    }
}



void Game::set_duck_start_position(int id, Position position){
    this->duck_exist(id);
    if(!this->map.set_duck_start_position(this->ducks[id], position.get_x(), position.get_y())){
        throw GameError("Duck start position is invalid");
    }
}

void Game::move_duck(int id, Position movement) {
    this->duck_exist(id);
    this->map.move_duck(this->ducks[id], movement.get_x(), movement.get_y());

    //this->ducks_states[id]->relative_movement = movement;
    // if(!this->map.move_duck(this->ducks[id], movement)){
    //     throw GameError("Duck movement is invalid");
    // } //quiero comentar esta exception pq que map.move_duck devuelva false ya no es un error.
}

std::vector<duck_DTO> Game::get_duck_DTO_list(){
    std::vector<duck_DTO> list_DTO;
    for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
       
        duck_DTO new_dto = it->second->to_DTO();
        new_dto.is_moving_left = this->ducks_states[it->first]->is_moving_left;
        new_dto.is_moving_right = this->ducks_states[it->first]->is_moving_right;
        
        new_dto.jumping = this->ducks_states[it->first]->is_jumping;
        new_dto.falling = this->ducks_states[it->first]->is_falling; 
        new_dto.is_alive = it->second->is_alive();  
        //new_dto.shooting = this->ducks_states[it->first].is_shooting;
        list_DTO.push_back(new_dto);
    }
    return list_DTO;
}

std::vector<bullet_DTO> Game::get_bullet_DTO_list(){
    std::vector<bullet_DTO> list_DTO;
    for(auto it = this->bullets.begin(); it != this->bullets.end(); it++){
        bullet_DTO new_dto = (*it)->to_DTO();
        list_DTO.push_back(new_dto);
    }
    return list_DTO;
}

std::vector<weapon_DTO> Game::get_weapon_DTO_list(){
    std::vector<weapon_DTO> list_DTO;
    for(auto it = this->weapons_on_map.begin(); it != this->weapons_on_map.end(); it++){
        weapon_DTO new_dto = (*it)->to_DTO();
        list_DTO.push_back(new_dto);
    }
    return list_DTO;
}


void Game::respawner(){
     for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
        if(!it->second->is_alive() && it->second->get_respawn_time() == 0){
            it->second->set_health(100);
        }
        else if(!it->second->is_alive()){
            it->second->tick_respawn_time();
        }
     }
}


void Game::continue_horizontal_movements(int count){
    
    for(int i=0; i< count; i++){
        for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
            if(!it->second->is_alive()){
                continue;
            }
            //se mueve para la left si is_moving_left is true
            if(this->ducks_states[it->first]->is_moving_left){
                this->ducks_states[it->first]->facing_direction = false;
                if(this->map.can_move_hitbox(it->second->get_hitbox(), LEFT_MOVEMENT,0)){
                    it->second->move_relative_to(LEFT_MOVEMENT,0);
                }
            }
            //se mueve para la right si is_moving_right is true
            if(this->ducks_states[it->first]->is_moving_right){
                this->ducks_states[it->first]->facing_direction = true;
                if(this->map.can_move_hitbox(it->second->get_hitbox(), RIGHT_MOVEMENT,0)){
                    it->second->move_relative_to(RIGHT_MOVEMENT,0);
                }            
            }  
        }       
    }
    for(int j=0; j<count*4; j++){
        for (auto it = bullets.begin(); it != bullets.end(); ) {
            if ((*it)->next_position(this->map)) {
                for (auto& duck : this->ducks) {
                    if(duck.second->get_hitbox().has_collision((*it)->get_hitbox())){
                        int numerito = (*it)->damage_generated(duck.second->get_id());
                        duck.second->receive_damage(numerito);
                        break;
                    }
                }
                ++it; 
            } else {
                it = bullets.erase(it);
            }
        }
    }


    for(int j=0; j< (count * 3); j++){
            for (auto it = weapons_on_map.begin(); it != weapons_on_map.end(); ) {
                if((*it)->is_moving() && (*it)->get_x_direction() > 0 && this->map.can_move_hitbox((*it)->get_hitbox(),RIGHT_MOVEMENT,0)){
                    (*it)->air_time_down_x();                    
                    (*it)->move_relative_to(RIGHT_MOVEMENT, 0);
                }
                else if((*it)->is_moving() && (*it)->get_x_direction() < 0 && this->map.can_move_hitbox((*it)->get_hitbox(),LEFT_MOVEMENT, 0)){
                    (*it)->air_time_down_x();                    
                    (*it)->move_relative_to(LEFT_MOVEMENT,0);       
                }
                
                ++it; 
            }
    } 

}

void Game::continue_vertical_movements(int count){

    for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
        if(this->ducks_states[it->first]->is_jumping){
            for(int i=0; i< (count * PRODUCT_FACTOR_JUMP) + ADD_FACTOR_JUMP; i++){
                if(this->ducks_states[it->first]->tiles_to_jump > 0){
                    //this->map.move_duck(it->second, 0, JUMP_DIRECTION);
                    if(this->map.can_move_hitbox(it->second->get_hitbox(),0, JUMP_DIRECTION)){
                        it->second->move_relative_to(0, JUMP_DIRECTION);
                    }
                    this->ducks_states[it->first]->tiles_to_jump --;
                }
                if(this->ducks_states[it->first]->tiles_to_jump == 0){
                    this->ducks_states[it->first]->air_time --;
                }
                if(this->ducks_states[it->first]->tiles_to_jump == 0 && this->ducks_states[it->first]->air_time == 0){         
                    this->ducks_states[it->first]->is_jumping = false;
                    this->ducks_states[it->first]->is_falling = true;
                }
            }
        }else if(this->ducks_states[it->first]->falling_with_style){
            for(int i=0; i< (count) + ADD_FACTOR_GRAVITY; i++){    
                if(this->ducks_states[it->first]->falling_with_style && i%2 == 0){//
                //    this->ducks_states[it->first]->is_falling = this->map.move_duck(it->second, 0, GRAVITY);
                    if(this->map.can_move_hitbox(it->second->get_hitbox(),0, GRAVITY)){
                        it->second->move_relative_to(0, GRAVITY);
                        this->ducks_states[it->first]->is_falling = true;
                    }
                    else{
                        this->ducks_states[it->first]->is_falling = false;
                    }
                }
            }
        }
        else{
            for(int i=0; i< (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; i++){
                //this->ducks_states[it->first]->is_falling = this->map.move_duck(it->second, 0, GRAVITY);
                if(this->map.can_move_hitbox(it->second->get_hitbox(),0, GRAVITY)){
                    it->second->move_relative_to(0, GRAVITY);
                    this->ducks_states[it->first]->is_falling = true;
                }
                else{
                    this->ducks_states[it->first]->is_falling = false;
                }
            }
        }  
    }
    
        for (auto it = weapons_on_map.begin(); it != weapons_on_map.end(); ){
             for(int j=0; j< (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; j++){
                (*it)->air_time_down();
                if(!(*it)->is_falling() && this->map.can_move_hitbox((*it)->get_hitbox(),0, JUMP_DIRECTION)){//
                    
                    (*it)->move_relative_to(0, JUMP_DIRECTION);
                    continue;                    
                }
                if((*it)->is_falling() && this->map.can_move_hitbox((*it)->get_hitbox(),0, GRAVITY)){
                    std::cout << "se cae" << std::endl;
                    (*it)->move_relative_to(0, GRAVITY);       
                }
            }
            ++it; 
        }    
}


void Game::stop_run_duck(int id, bool stop_left, bool stop_right){
    this->duck_exist(id);
    if(stop_left){
        this->ducks_states[id]->is_moving_left = !stop_left;
    }
    if(stop_right){
        this->ducks_states[id]->is_moving_right = !stop_right;
    }
}

Position Game::position_duck(int id){
    this->duck_exist(id);
    return this->ducks[id]->get_position();
}

game_snapshot_t Game::get_snapshot(){
    game_snapshot_t snapshot;
    snapshot.ducks_len = this->ducks.size();
    snapshot.ducks = this->get_duck_DTO_list();
    snapshot.bullets_len = this->bullets.size();
    snapshot.bullets = this->get_bullet_DTO_list();
    snapshot.weapons = this->get_weapon_DTO_list();
    snapshot.weapons_len = snapshot.weapons.size();
    return snapshot;
}

map_structure_t Game::get_map_structure(){
    map_structure_t map_structure;
    map_structure.platforms = this->map.get_platforms_DTO();
    map_structure.platforms_len = static_cast<uint16_t>(map_structure.platforms.size());
    return map_structure;
}

void Game::jump_duck(int id, bool jump){
    if(!this->ducks[id]->is_alive()){
        return;
    }
    this->duck_exist(id);
    if(jump){
        this->ducks_states[id]->falling_with_style = true;
    }
    if(!this->ducks_states[id]->is_jumping && jump && !this->ducks_states[id]->is_falling){//esto no es suficiente para evitar que vuele
        
        this->ducks_states[id]->is_jumping = true;
        this->ducks_states[id]->tiles_to_jump = TILES_FOR_JUMP;
        this->ducks_states[id]->air_time = 40;
    }
    if(jump && this->ducks_states[id]->is_falling){
        this->ducks_states[id]->falling_with_style = true;
    }
}

void Game::stop_jump_duck(int id, bool stop_jump){
    if(stop_jump){
        this->ducks_states[id]->falling_with_style = false;
    }
}

void Game::fire_duck_weapon(int id, bool fire){
    if(fire && this->ducks[id]->is_alive()){
        this->ducks_states[id]->is_shooting = true;
    }
}

void Game::keep_shooting(){
    
    for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
        it->second->continue_fire_rate();
        std::vector<std::shared_ptr<BulletInterface>> new_bullets;
        if(this->ducks_states[it->first]->is_shooting && this->ducks_states[it->first]->facing_direction){
            new_bullets = it->second->fire_weapon(1, 0, this->map);
        }
        if(this->ducks_states[it->first]->is_shooting && !this->ducks_states[it->first]->facing_direction){
            new_bullets = it->second->fire_weapon(-1, 0, this->map);
        }
        int size = new_bullets.size();
        for(int i = 0; i < size; i++){
            this->bullets.push_back(new_bullets[i]);
        }
    }
}

void Game::stop_duck_weapon(int id, bool stop_fire){
    if(stop_fire){
        this->ducks_states[id]->is_shooting = false;
        return;
    }
}


void Game::add_invalid_position(Hitbox hitbox){
    if(!this->map.add_invalid_position(hitbox)){
        throw GameError("game can't add invalid position");
    }
}

void Game::add_new_platform(Hitbox hitbox){
    if(!this->map.add_platform(hitbox)){
        throw GameError("game can't add invalid position");
    }
}

void Game::add_weapon_on_map(std::string type_weapon, int x, int y){
    std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>(WeaponFactory::createWeapon(type_weapon));
    if(!this->map.can_move_hitbox(weapon->get_hitbox(), x, y)){
        throw GameError("game can't add weapon to map");
    }
    weapon->move_to(x, y);
    this->weapons_on_map.push_back(weapon);
}




/// /DUCK MOVEMENTS SACAR CODIGO REPETIDO, NO TIENE LAS BALAS

// void Game::move_duck_if_possible(Duck* duck, DuckState* duck_state, int direction, bool facing_direction) {
//     duck_state->facing_direction = facing_direction;
//     if (this->map.can_move_hitbox(duck->get_hitbox(), direction, 0)) {
//         duck->move_relative_to(direction, 0);
//     }
// }

// void Game::continue_horizontal_movements(int count) {
//     for (int i = 0; i < count; i++) {
//         for (auto it = this->ducks.begin(); it != this->ducks.end(); ++it) {
//             if (!it->second->is_alive()) {
//                 continue;
//             }
//             auto duck_state = this->ducks_states[it->first];
//             auto duck = it->second;

//             if (duck_state->is_moving_left) {
//                 move_duck_if_possible(duck, duck_state, LEFT_MOVEMENT, false);
//             }
//             if (duck_state->is_moving_right) {
//                 move_duck_if_possible(duck, duck_state, RIGHT_MOVEMENT, true);
//             }
//         }

//     }
// }
