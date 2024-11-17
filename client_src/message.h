#ifndef MESSAGE_H
#define MESSAGE_H

#include "../common_src/game_snapshot_t.h"


class Message{

protected:
    uint8_t code_id = 0;
    game_snapshot_t gs;
    map_structure_t map;
    score_DTO score;

public:

    Message(int code);
    uint8_t get_code();
    game_snapshot_t get_game_snapshot();
    map_structure_t get_map();
    score_DTO get_score();

    void set_gs(game_snapshot_t gs);
    void set_map(map_structure_t map);
    void set_score(score_DTO score);

    ~Message();
};


#endif