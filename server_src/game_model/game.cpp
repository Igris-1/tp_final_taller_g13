#include "game.h"

Game::Game(int high, int width): map(high, width), id(0), ducks_states(), ducks() {}

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
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    if(!this->ducks_states[id]->is_moving_left){
        this->ducks_states[id]->is_moving_left = left;
    }
    if(!this->ducks_states[id]->is_moving_right){
        this->ducks_states[id]->is_moving_right = right;
    }
}


void Game::set_duck_start_position(int id, Position position){
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    if(!this->map.set_duck_start_position(this->ducks[id], position)){
        throw GameError("Duck start position is invalid");
    }
}

void Game::move_duck(int id, Position movement) {
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    //this->ducks_states[id]->relative_movement = movement;
    if(!this->map.move_duck(this->ducks[id], movement)){
        throw GameError("Duck movement is invalid");
    }
}

std::vector<duck_DTO> Game::get_duck_DTO_list(){
    std::vector<duck_DTO> list_DTO;
    for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
        duck_DTO new_dto = it->second->to_DTO();
        new_dto.is_moving_left = this->ducks_states[it->first]->is_moving_left;
        new_dto.is_moving_right = this->ducks_states[it->first]->is_moving_right;
        
        //new_dto.jumping = this->ducks_states[it->first].is_jumping;
        //new_dto.shooting = this->ducks_states[it->first].is_shooting;
        list_DTO.push_back(new_dto);
    }
    return list_DTO;
}

void Game::continue_movements(){
    for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
        //se mueve para la left si is_moving_left is true
        if(this->ducks_states[it->first]->is_moving_left){
            Position movement(LEFT_MOVEMENT, 0);
            this->map.move_duck(it->second, movement);
            std::cout << "Moving left" << std::endl;
        }
        //se mueve para la right si is_moving_right is true
        if(this->ducks_states[it->first]->is_moving_right){
            Position movement(RIGHT_MOVEMENT, 0);
            this->map.move_duck(it->second, movement);
            std::cout << "Moving right" << std::endl;
        }
        
        if(this->ducks_states[it->first]->is_jumping && this->ducks_states[it->first]->tiles_to_jump > 0){
            this->map.move_duck(it->second, Position(0,-1));
            this->ducks_states[it->first]->tiles_to_jump --;
        }else{
            //this->map.move_duck(it->second, Position(0, 1));
        }
    }
}

void Game::stop_run_duck(int id, bool stop_left, bool stop_right){
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    if(stop_left){
        std::cout << " STOP Moving left" << std::endl;
        this->ducks_states[id]->is_moving_left = !stop_left;
    }
    if(stop_right){
        std::cout << " STOP Moving right" << std::endl;
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

// void Game::jump_duck(int id, bool jump){
//     if(this->ducks.find(id) == this->ducks.end()){
//         throw GameError("Duck id not found");
//     }
//     this->ducks_states[id]->is_jumping = true;
//     this->ducks_states[id]->tiles_to_jump = JUMP_SIZE;
// }

void Game::add_invalid_position(Position invalid_position){
    if(!this->map.add_invalid_position(invalid_position)){
        throw GameError("game can't add invalid position");
    }
}