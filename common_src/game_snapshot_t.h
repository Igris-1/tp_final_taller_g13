#ifndef GAME_SNAPSHOT_T_H
#define GAME_SNAPSHOT_T_H

#include <string>
#include <cstdint>
#include <vector>
#include "duck_DTO.h"


/*
typedef struct game_snapshot {
    uint16_t ducks_len;           // 2 bytes
    //std::vector<duck> ducks;      // Vector que contendrá los ducks
}game_snapshot_t;
*/

typedef struct game_snapshot {
    
    uint8_t ducks_len; //2 bytes
    std::vector<duck_DTO> ducks; // sizeof(ducks) * ducks_len
    
    //uint16_t bullets_len; //2 bytes
    //Bullet bullets[]; // sizeof(bullet) * bullets_len
    
   
    //uint16_t items_len; //2 bytes
    //Item items[]; // sizeof(item) * items_len

} game_snapshot_t;

//__attribute__((packed))

#endif  // GAME_SNAPSHOT_T_H