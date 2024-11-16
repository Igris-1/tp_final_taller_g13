#ifndef MESSAGE_H
#define MESSAGE_H

#include "../common_src/game_snapshot_t.h"


class Message{

protected:
    uint8_t code_id = 0;
    game_snapshot_t gs;
    map_structure_t map;

public:

    Message(int code);
    uint8_t get_code();
    game_snapshot_t get_game_snapshot();
    map_structure_t get_map();

    void set_gs(game_snapshot_t gs);
    void set_map(map_structure_t map);

    ~Message();
};


#endif