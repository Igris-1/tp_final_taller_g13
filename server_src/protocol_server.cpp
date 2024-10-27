//COSAS A ENVIAR
// 0x00 -> mandar mapa y spawns etc (todo lo inicial)
// 0x01 -> snapshot
// 0x02 -> fin de partida (manda puntajes)

//COSAS A RECIBIR
// 0x00 -> conectarse al server -> (cant_jugadores | name | segundo name)
// 0x01 -> durante la partida -> (id_player | id_accion)

//Estructura the screen final de partida:
//GANADOR PEDRO PTS 10
//2NDO    FRAN  PTS 09
//3ER     NICO  PTS 06
//4TO     FEDE  PTS 00

#include "protocol_server.h"
#include <cstdint>
#include "../common_src/liberror.h"
#include <string.h>
#include <arpa/inet.h>

#define ONE_BYTE 1
#define SHUT_DOWN_TWO 2


ProtocolServer::ProtocolServer(Socket&& client) 
        : connection(std::move(client)), socket_is_closed(false) {}

bool ProtocolServer::socket_closed(){
    return socket_is_closed;
}

action_t ProtocolServer::read_action() {

    uint8_t code;
    action_t action;

    action_t nullAction;

    int direcciones[4];
    
    for (int i = 0; i < 4; i++) {
        if (connection.recvall(&code, ONE_BYTE, &socket_is_closed) != 1) {
            return nullAction;
        }
        direcciones[i] = code;
    }

    action.left = direcciones[0];
    action.right = direcciones[1];
    action.up = direcciones[2];
    action.down = direcciones[3];

    return action;
}

//void ProtocolServer::sendGameInfo(game_snapshot_t command, bool* was_closed) {}


void ProtocolServer::shutDown() {
    if (!socket_is_closed) {
        connection.shutdown(SHUT_DOWN_TWO);
    }
}

ProtocolServer::~ProtocolServer(){
    connection.close();
}

