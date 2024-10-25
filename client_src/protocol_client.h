#pragma once






//COSAS A ENVIAR AL SERVIDOR
// 0x00 -> conectarse al server -> (cant_jugadores | name | segundo name) 
// 0x01 -> durante la partida -> (id_player | id_accion)

/*
typedef enum{
    LEFT = 0,
    RIGHT,
    DOWN,
    UP,
    
    /*TOGGLE_SHOOT,
    JUMP,
    CHANGE_WEAPON, // estos 3 serian pickups no change no?
    CHANGE_HELMET,
    CHANGE_ARMOR,
}action_t;*/


//COSAS A RECIBIR

// 0x00 -> mandar mapa y spawns etc (todo lo inicial)
// 0x01 -> snapshot
// 0x02 -> estado de partida (manda puntajes) esto hay q hacerlo cada 5 rondas
// 0x03 -> fin de partida (manda puntajes)

//Estructura the screen final de partida:
//GANADOR PEDRO PTS 10
//2NDO    FRAN  PTS 09
//3ER     NICO  PTS 06
//4TO     FEDE  PTS 00

// typedef enum{
//     Explosive = 0,
//     Automatic,
//     SemiAutomatic,

// }GunType_t;



/*// Estado del pato
typedef struct{
    uint8_t duck_id; // id del color del pato?
    Position pos;
    uint8_t duck_hp;
    bool shooting;
    bool running;
    bool jumping;
    bool weapon_equipped;
    bool helmet_equipped;
    bool armor_equipped;
    
    int id_arma; // 1 = pistola / 2 = escopeta
}Duck;*/

// Objetos en el suelo
/*typedef struct{
    int id; // id, ejemplo: 1, es cacsco, 2 es escopeta, 3 caja....
    Position pos;
}Item;*/


// Estado de las balas
/*typedef struct{
    int bullet_type;
    Position pos;
    std::tuple<int, int> direction;
    // (0, -1) arriba 
    // (0, 1)  abajo
    // (1, 0)  derecha
    // (-1, 0) izq
}Bullet;*/