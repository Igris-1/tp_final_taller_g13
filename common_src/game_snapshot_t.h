#ifndef GAME_SNAPSHOT_T_H
#define GAME_SNAPSHOT_T_H

#include <cstdint>
#include <string>
#include <vector>

#include "DTOs.h"



typedef struct game_snapshot {

    uint8_t ducks_len = 0; 
    std::vector<duck_DTO> ducks; 

    uint16_t bullets_len = 0;
    std::vector<bullet_DTO> bullets; 

    uint16_t weapons_len = 0;
    std::vector<weapon_DTO> weapons;

    uint16_t boxes_len = 0;
    std::vector<box_DTO> boxes;

    sounds_DTO sounds;
} game_snapshot_t;

typedef struct map_structure_t {
    uint16_t width;
    uint16_t height;
    uint16_t platforms_len = 0;
    std::vector<platform_DTO> platforms;
    uint16_t spawns_platforms_len = 0;
    std::vector<platform_DTO> spawns_platforms;
} map_structure_t;

#endif  // GAME_SNAPSHOT_T_H