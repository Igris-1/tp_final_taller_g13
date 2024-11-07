#include "game.h"

Game::Game(int height, int width): map(width, height), ducks_states(), ducks() {}

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
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    this->ducks.erase(id);
    this->ducks_states.erase(id);
}


void Game::run_duck(int duck_id, bool left, bool right){
    if(this->ducks.find(duck_id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    if(!this->ducks_states[duck_id]->is_moving_left){
        this->ducks_states[duck_id]->is_moving_left = left;
    }
    if(!this->ducks_states[duck_id]->is_moving_right){
        this->ducks_states[duck_id]->is_moving_right = right;
    }
}


void Game::set_duck_start_position(int id, Position position){
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    if(!this->map.set_duck_start_position(this->ducks[id], position.get_x(), position.get_y())){
        throw GameError("Duck start position is invalid");
    }
}

void Game::move_duck(int id, Position movement) {
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
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
        //new_dto.shooting = this->ducks_states[it->first].is_shooting;
        list_DTO.push_back(new_dto);
    }
    return list_DTO;
}

void Game::continue_horizontal_movements(int count){
    for(int i=0; i< count; i++){
        for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
            //se mueve para la left si is_moving_left is true
            if(this->ducks_states[it->first]->is_moving_left){
                //Position movement(LEFT_MOVEMENT, 0);
                this->map.move_duck(it->second, LEFT_MOVEMENT, 0);
            }
            //se mueve para la right si is_moving_right is true
            if(this->ducks_states[it->first]->is_moving_right){
                //Position movement(RIGHT_MOVEMENT, 0);
                this->map.move_duck(it->second, RIGHT_MOVEMENT, 0);               
            }  
        }
    }
}

void Game::continue_vertical_movements(int count){
    for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
        if(this->ducks_states[it->first]->is_jumping){
            for(int i=0; i< (count * PRODUCT_FACTOR_JUMP) + ADD_FACTOR_JUMP; i++){
                if(this->ducks_states[it->first]->tiles_to_jump > 0){
                    this->map.move_duck(it->second, 0, JUMP_DIRECTION);
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
                    this->ducks_states[it->first]->is_falling = this->map.move_duck(it->second, 0, GRAVITY);
                }
            }
        }
        else{
            for(int i=0; i< (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; i++){
                this->ducks_states[it->first]->is_falling = this->map.move_duck(it->second, 0, GRAVITY);
            }
        }
    }
}


void Game::stop_run_duck(int id, bool stop_left, bool stop_right){
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    if(stop_left){
        this->ducks_states[id]->is_moving_left = !stop_left;
    }
    if(stop_right){
        this->ducks_states[id]->is_moving_right = !stop_right;
    }
}

Position Game::position_duck(int id){
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    return this->ducks[id]->get_position();
}

game_snapshot_t Game::get_snapshot(){
    game_snapshot_t snapshot;
    snapshot.ducks_len = this->ducks.size();
    snapshot.ducks = this->get_duck_DTO_list();
    return snapshot;
}

map_structure_t Game::get_map_structure(){
    map_structure_t map_structure;
    map_structure.platforms = this->map.get_platforms_DTO();
    map_structure.platforms_len = static_cast<uint16_t>(map_structure.platforms.size());
    return map_structure;
}

void Game::jump_duck(int id, bool jump){
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
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