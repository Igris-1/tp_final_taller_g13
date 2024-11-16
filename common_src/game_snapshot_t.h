#ifndef GAME_SNAPSHOT_T_H
#define GAME_SNAPSHOT_T_H

#include <cstdint>
#include <string>
#include <vector>

#include "duck_DTO.h"


/*
typedef struct game_snapshot {
    uint16_t ducks_len;           // 2 bytes
    //std::vector<duck> ducks;      // Vector que contendrá los ducks
}game_snapshot_t;
*/

typedef struct game_snapshot {

    uint8_t ducks_len = 0;            // 1 byte
    std::vector<duck_DTO> ducks;  // sizeof(ducks) * ducks_len

    uint16_t bullets_len = 0;             // 2 bytes
    std::vector<bullet_DTO> bullets;  // sizeof(bullet) * bullets_len

    uint16_t weapons_len = 0;             // 2 bytes
    std::vector<weapon_DTO> weapons;  // sizeof(item) * items_len

} game_snapshot_t;

typedef struct map_structure_t {
    uint16_t platforms_len = 0;
    std::vector<platform_DTO> platforms;
} map_structure_t;

//__attribute__((packed))

#endif  // GAME_SNAPSHOT_T_H