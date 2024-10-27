#ifndef GAME_SNAPSHOT_T_H
#define GAME_SNAPSHOT_T_H

#include <string>
#include <cstdint>
#include <vector>

/*typedef struct game_snapshot {

    int tamanio vector_ducks;
    std::vector<ducks>ducks;

    int tamanio vector_bullets;
    std::vector<bullets>bullets;

    int tamanio vector_items;
    std::vector<items>items;

} game_snapshot_t;*/



typedef struct game_snapshot {
    uint16_t ducks_len;           // 2 bytes
    //std::vector<duck> ducks;      // Vector que contendrá los ducks
}game_snapshot_t;

#endif  // GAME_SNAPSHOT_T_H