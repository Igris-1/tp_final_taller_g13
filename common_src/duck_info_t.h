#ifndef DUCK_INFO_T_H
#define DUCK_INFO_T_H
#include <cstdint>


typedef struct duck_info {
    
    uint8_t duck_id; // id del color del pato?
    uint16_t x;
    uint16_t y;
    //uint8_t duck_hp;
    //bool shooting;
    bool running;
    //bool jumping;
    //bool weapon_equipped;
    //bool helmet_equipped;
    //bool armor_equipped;

    //int id_arma; // 1 = pistola / 2 = escopeta

} duck_TDO;



#endif  // DUCK_INFO_T_H