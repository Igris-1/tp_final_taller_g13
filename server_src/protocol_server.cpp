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

#define TWO_BYTES 2
#define ONE_BYTE 1
#define NULL_COMMAND 0

#define SHUT_DOWN_TWO 2


ProtocolServer::ProtocolServer(Socket client):connection(std::move(client)) {}


ProtocolServer::ProtocolServer(ProtocolServer&& other) noexcept: connection(std::move(other.connection)) {}


void ProtocolServer::sendStringToClient(const char* message, bool* was_closed) {

    int len = strlen(message);
    uint16_t bigendian = htons(len);
    connection.sendall(&bigendian, TWO_BYTES, was_closed); //send del tamaño del string
    connection.sendall(message, len, was_closed); //send del string

}

void ProtocolServer::sendOneByteToClient(const uint8_t* data, bool* was_closed) {
    connection.sendall(data, ONE_BYTE, was_closed);
}

action_t ProtocolServer::receiveDataFromClient(bool* was_closed) {

    uint8_t code;
    action_t action;

    action_t nullAction;

    //un receive pedorro temporal para recibir 4 ints q represtenan direcciones
    int direcciones[4];
    
    for (int i = 0; i < 4; i++) {
        if (connection.recvall(&code, ONE_BYTE, was_closed) != 1) {
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

void ProtocolServer::sendGameInfo(game_snapshot_t command, bool* was_closed) {

}


void ProtocolServer::shutDown() {
    try {
        connection.shutdown(SHUT_DOWN_TWO);
        connection.close();
    } catch (const LibError&) {}
}

ProtocolServer::~ProtocolServer(){}

