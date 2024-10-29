#include "game.h"

Game::Game(int high, int width): map(high, width) {
    id = 0;
}


int Game::add_duck(int health) {
    std::shared_ptr<Duck> new_duck = std::make_shared<Duck>(health, id);
    id++;
    this->ducks[id] = new_duck;
    this->ducks_states.emplace(id, duck_state{Position(0,0), false, false, false});
    return id -1;
}

void Game::run_duck(int id, Position movement){
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    this->ducks_states[id].is_running = true;
    this->ducks_states[id].relative_movement = movement;
}

void Game::set_duck_start_position(int id, Position position){
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    if(!this->map.set_duck_start_position(this->ducks[id], position)){
        throw GameError("Duck start position is invalid");
    }
        this->ducks_states[id].is_running = false;
}

void Game::move_duck(int id, Position movement) {
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    if(!this->map.move_duck(this->ducks[id], movement)){
        throw GameError("Duck movement is invalid");
    }
}

std::vector<duck_DTO> Game::get_duck_DTO_list(){
    std::vector<duck_DTO> list_DTO;
    for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
        duck_DTO new_dto = it->second->to_DTO();
        new_dto.running = this->ducks_states[it->first].is_running;
        //new_dto.jumping = this->ducks_states[it->first].is_jumping;
        //new_dto.shooting = this->ducks_states[it->first].is_shooting;
        list_DTO.push_back(it->second->to_DTO());
    }
    return list_DTO;
}

void Game::continue_movements(){
    for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
        if(this->ducks_states[it->first].is_running){
            this->map.move_duck(it->second, this->ducks_states[it->first].relative_movement);
        }
    }
}

void Game::stop_duck(int id){
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    this->ducks_states[id].is_running = false;
}

Position Game::position_duck(int id){
    if(this->ducks.find(id) == this->ducks.end()){
        throw GameError("Duck id not found");
    }
    return this->ducks[id]->get_position();
}