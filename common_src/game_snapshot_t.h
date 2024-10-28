#ifndef GAME_SNAPSHOT_T_H
#define GAME_SNAPSHOT_T_H

#include <string>
#include <cstdint>
#include <vector>
#include "duck_info_t.h"


/*
typedef struct game_snapshot {
    uint16_t ducks_len;           // 2 bytes
    //std::vector<duck> ducks;      // Vector que contendrá los ducks
}game_snapshot_t;
*/

typedef struct game_snapshot {
    
    uint16_t ducks_len; //2 bytes
    duck_TDO ducks[]; // sizeof(ducks) * ducks_len
    
    //uint16_t bullets_len; //2 bytes
    //Bullet bullets[]; // sizeof(bullet) * bullets_len
    
   
    //uint16_t items_len; //2 bytes
    //Item items[]; // sizeof(item) * items_len

} game_snapshot_t;



#endif  // GAME_SNAPSHOT_T_H