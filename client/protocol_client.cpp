
//COSAS A ENVIAR AL SERVIDOR
// 0x00 -> conectarse al server -> (cant_jugadores | name | segundo name) 
// 0x01 -> durante la partida -> (id_player | id_accion)


typedef enum{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    TOGGLE_SHOOT,
    JUMP,
    CHANGE_WEAPON,
    CHANGE_HELMET,
    CHANGE_ARMOR,
}action_t;


//COSAS A RECIBIR

// 0x00 -> mandar mapa y spawns etc (todo lo inicial)
// 0x01 -> snapshot
// 0x02 -> fin de partida (manda puntajes)

//Estructura the screen final de partida:
//GANADOR PEDRO PTS 10
//2NDO    FRAN  PTS 09
//3ER     NICO  PTS 06
//4TO     FEDE  PTS 00