#ifndef MESSAGE_H
#define MESSAGE_H
#include <cstdint>

#include "../common_src/game_snapshot_t.h"

typedef struct instruction_for_client_t {

    uint8_t id = 0;
    game_snapshot_t gs;
    map_structure_t map;
    score_DTO score;

} instruction_for_client_tlient_action_t;

#endif