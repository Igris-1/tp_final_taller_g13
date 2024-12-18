#ifndef DTOS_H
#define DTOS_H
#include <cstdint>

typedef struct duck_DTO {
    uint8_t duck_id;  // id del color del pato
    uint16_t x;
    uint16_t y;
    bool is_moving_right = false;
    bool is_moving_left = false;
    bool shooting = false;
    bool jumping = false;
    bool falling = false;
    uint16_t width;
    uint16_t height;
    bool is_alive = true;
    uint8_t weapon_id = 0;
    bool helmet_equipped;
    bool armor_equipped;
    bool looking_up = false;
    bool crouching = false;
} __attribute__((packed)) duck_DTO;

// es necesario el packed aca, no lo saquen
// va, en teoria es mandatorio pq distintos compiladores pueden agregar distinto padding
// al struct, entonces si no se pone packed, el padding puede hacer que el tamanio de la
// estructura que se recibe sea distinto
//  al que estoy recibiendo, pero como es todo en una sola pc, no deberia haber problema.
//  igual, no lo saquemos.


typedef struct platform_DTO {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} __attribute__((packed)) platform_DTO;

typedef struct bullet_DTO {
    uint8_t bullet_id;  // id del tipo de bala
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    int8_t x_direction;
    int8_t y_direction;
} __attribute__((packed)) bullet_DTO;


typedef struct weapon_DTO {
    uint8_t weapon_id;  // id del tipo de arma
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} __attribute__((packed)) weapon_DTO;


typedef struct score_DTO {
    uint8_t amount_of_ducks = 0;
    uint8_t first_place_id = 0;
    uint8_t second_place_id = 0;
    uint8_t third_place_id = 0;
    uint8_t fourth_place_id = 0;

    uint8_t first_place_score = 0;
    uint8_t second_place_score = 0;
    uint8_t third_place_score = 0;
    uint8_t fourth_place_score = 0;

} __attribute__((packed)) score_DTO;

typedef struct box_DTO {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} __attribute__((packed)) box_DTO;

typedef struct games_DTO {
    uint8_t game_id;
    uint8_t max_players;
    uint8_t current_players;
} __attribute__((packed)) games_DTO;



typedef struct sounds_DTO {
    bool death = false;
    bool shooting_small_weapon = false;
    bool shooting_big_weapon = false;
    bool shooting_laser_weapon = false;
    bool explotion = false;
    bool duck_sliding = false;
    bool shotgun_recharging = false;
    bool sniper_recharging = false;
    bool duck_struck = false;
} __attribute__((packed)) sounds_DTO;


#endif  // DUCK_INFO_T_H