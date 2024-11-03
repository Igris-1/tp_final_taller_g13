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
#include <iostream>
#include "duck_DTO.h"

#define ONE_BYTE 1
#define TWO_BYTES 2
#define SHUT_DOWN_TWO 2
#define ACTION_SIZE 7


ProtocolServer::ProtocolServer(Socket&& client) 
        : connection(std::move(client)), socket_is_closed(false) {}

bool ProtocolServer::socket_closed(){
    return socket_is_closed;
}

action_t ProtocolServer::receive_action() {
    try{ 
        uint8_t code;
        action_t action;

        action_t nullAction;

        int actions_vector[ACTION_SIZE];// OJO ESTO
        
        for (int i = 0; i < ACTION_SIZE ; i++) { //cambiar a 7 para incluir el jump
            connection.recvall(&code, ONE_BYTE, &socket_is_closed);
            actions_vector[i] = code;
        }
        
        action.left = actions_vector[0];
        action.right = actions_vector[1];
        action.up = actions_vector[2];
        action.down = actions_vector[3];
        action.stop_right = actions_vector[4];
        action.stop_left = actions_vector[5];
        action.jump = actions_vector[6];

        return action;
    } catch (const LibError& e) {
        socket_is_closed = true;
        throw;
    }
}

void ProtocolServer::sendGameInfo(game_snapshot_t game_snapshot) {
    connection.sendall(&game_snapshot.ducks_len, ONE_BYTE, &socket_is_closed);


    for(uint8_t i = 0; i<game_snapshot.ducks_len; i++){
        connection.sendall(&game_snapshot.ducks[i], sizeof(duck_DTO), &socket_is_closed);
    }

}


void ProtocolServer::shutDown() {
    if (!socket_is_closed) {
        connection.shutdown(SHUT_DOWN_TWO);
    }
}

ProtocolServer::~ProtocolServer(){
    connection.close();
}

