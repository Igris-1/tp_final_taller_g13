#ifndef DUCK_INFO_T_H
#define DUCK_INFO_T_H
#include <cstdint>


typedef struct duck_DTO {
    
    uint8_t duck_id; // id del color del pato?
    uint8_t x;
    uint8_t y;
    bool running;
    //uint8_t duck_hp;
    //bool shooting;
    //bool jumping;
    //bool weapon_equipped;
    //bool helmet_equipped;
    //bool armor_equipped;

    //int id_arma; // 1 = pistola / 2 = escopeta

}duck_DTO; 

#endif  // DUCK_INFO_T_H