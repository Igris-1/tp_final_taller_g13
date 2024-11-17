#include "message.h"


Message::Message(int code): code_id(code) {}

uint8_t Message::get_code(){
    return this->code_id;
}
game_snapshot_t Message::get_game_snapshot(){
    return this->gs;
}
map_structure_t Message::get_map(){
    return this->map;
}

score_DTO Message::get_score(){
    return this->score;
}

void Message::set_gs(game_snapshot_t gs){
    this->gs = gs;
}

void Message::set_map(map_structure_t map){
    this->map = map;
}

void Message::set_score(score_DTO score){
    this->score = score;
}

Message::~Message() {}
