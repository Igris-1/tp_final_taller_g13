#ifndef DUCK_INFO_T_H
#define DUCK_INFO_T_H
#include <cstdint>


typedef struct duck_DTO {
    
    uint8_t duck_id; // id del color del pato
    uint16_t x;
    uint16_t y;
    bool is_moving_right = false;
    bool is_moving_left = false; 
    //uint8_t duck_hp;
    //bool shooting;
    bool jumping = false;
    bool falling = false;
    uint16_t width;
    uint16_t height;
    bool is_alive = true;
    uint8_t weapon_id = 0;
    //bool helmet_equipped;
    //bool armor_equipped;

    //int id_arma; // 1 = pistola / 2 = escopeta

}__attribute__((packed)) duck_DTO;  //es necesario el packed aca, no lo saquen
                                    //va, en teoria es mandatorio pq distintos compiladores pueden agregar distinto padding al struct, entonces
                                    //si no se pone packed, el padding puede hacer que el tamanio de la estructura que se recibe sea distinto 
                                    // al que estoy recibiendo, pero como es todo en una sola pc, no deberia haber problema. igual, no lo saquemos.


typedef struct platform_DTO{
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
}__attribute__((packed)) platform_DTO;

typedef struct bullet_DTO{
    uint8_t bullet_id; // id del tipo de bala
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint16_t x_direction;
    uint16_t y_direction;
}__attribute__((packed)) bullet_DTO;


typedef struct weapon_DTO{
    uint8_t weapon_id; // id del tipo de arma
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
}__attribute__((packed)) weapon_DTO;
#endif  // DUCK_INFO_T_H