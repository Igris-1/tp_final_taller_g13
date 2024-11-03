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
#include "../common_src/translator_actions.h"
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include "duck_DTO.h"
#include <bitset>

#define ONE_BYTE 1
#define TWO_BYTES 2
#define SHUT_DOWN_TWO 2
#define ACTION_SIZE 8


ProtocolServer::ProtocolServer(Socket&& client) 
        : connection(std::move(client)), socket_is_closed(false) {}

bool ProtocolServer::socket_closed(){
    return socket_is_closed;
}

action_t ProtocolServer::receive_action() {
    try{ 
        uint8_t code;
        action_t action;
        
        uint16_t action_16bits;
        connection.recvall(&action_16bits, 2, &socket_is_closed);
        TranslatorActions translator;
        translator.translate_flags(action_16bits, action.left, action.right, action.up, action.down, action.stop_right, action.stop_left, action.jump, action.stop_jump);

        return action;
    } catch (const LibError& e) {
        socket_is_closed = true;
        throw;
    }
}

void ProtocolServer::sendGameInfo(game_snapshot_t game_snapshot) {
    connection.sendall(&game_snapshot.ducks_len, ONE_BYTE, &socket_is_closed);

    //std::cout << "x: " << game_snapshot.ducks[0].x << "y: " << game_snapshot.ducks[0].y << std::endl;

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

