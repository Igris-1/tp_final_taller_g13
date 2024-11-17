// COSAS A ENVIAR
//  0x00 -> mandar mapa y spawns etc (todo lo inicial)
//  0x01 -> snapshot
//  0x02 -> fin de partida (manda puntajes)

// COSAS A RECIBIR
//  0x00 -> conectarse al server -> (cant_jugadores | name | segundo name)
//  0x01 -> durante la partida -> (id_player | id_accion)

// Estructura the screen final de partida:
// GANADOR PEDRO PTS 10
// 2NDO    FRAN  PTS 09
// 3ER     NICO  PTS 06
// 4TO     FEDE  PTS 00

#include "protocol_server.h"

#include <bitset>
#include <cstdint>
#include <iostream>

#include <arpa/inet.h>
#include <string.h>

#include "../common_src/liberror.h"
#include "../common_src/translator_actions.h"

#include "duck_DTO.h"

#define ONE_BYTE 1
#define TWO_BYTES 2
#define SHUT_DOWN_TWO 2
#define ACTION_SIZE 8


ProtocolServer::ProtocolServer(Socket&& client):
        connection(std::move(client)), socket_is_closed(false) {}

bool ProtocolServer::socket_closed() { return socket_is_closed; }

action_t ProtocolServer::receive_action() {
    try {
        uint8_t code;
        action_t action;

        uint16_t action_16bits;
        connection.recvall(&action_16bits, TWO_BYTES, &socket_is_closed);
        TranslatorActions translator;
        translator.translate_flags(action_16bits, action.left, action.right, action.up, action.down,
                                   action.stop_right, action.stop_left, action.jump,
                                   action.stop_jump, action.press_action_button,
                                   action.unpress_action_button, action.press_pick_up_button,
                                   action.unpress_pick_up_button);
        connection.recvall(&action.player_id, ONE_BYTE, &socket_is_closed);
        return action;
    } catch (const LibError& e) {
        socket_is_closed = true;
        throw;
    }
}

int ProtocolServer::receive_number_of_players() {
    uint8_t buffer;
    connection.recvall(&buffer, ONE_BYTE, &socket_is_closed);
    return buffer;
}


void ProtocolServer::sendGameInfo(game_snapshot_t game_snapshot) {
    std::lock_guard<std::mutex> lock(mutex);
    uint8_t protocol_name = 0x01;
    connection.sendall(&protocol_name, ONE_BYTE, &socket_is_closed);

    connection.sendall(&game_snapshot.ducks_len, ONE_BYTE, &socket_is_closed);
    for (uint8_t i = 0; i < game_snapshot.ducks_len; i++) {
        connection.sendall(&game_snapshot.ducks[i], sizeof(duck_DTO), &socket_is_closed);
    }

    connection.sendall(&game_snapshot.bullets_len, TWO_BYTES, &socket_is_closed);
    for (uint16_t i = 0; i < game_snapshot.bullets_len; i++) {
        connection.sendall(&game_snapshot.bullets[i], sizeof(bullet_DTO), &socket_is_closed);
    }
    connection.sendall(&game_snapshot.weapons_len, TWO_BYTES, &socket_is_closed);
    for (uint16_t i = 0; i < game_snapshot.weapons_len; i++) {
        connection.sendall(&game_snapshot.weapons[i], sizeof(weapon_DTO), &socket_is_closed);
    }
}

void ProtocolServer::sendGameStartInfo(map_structure_t map_structure) {
    std::lock_guard<std::mutex> lock(mutex);
    uint8_t protocol_name = 0x00;
    connection.sendall(&protocol_name, ONE_BYTE, &socket_is_closed);
    connection.sendall(&map_structure.platforms_len, TWO_BYTES, &socket_is_closed);
    for (int i = 0; i < map_structure.platforms_len; i++) {
        connection.sendall(&map_structure.platforms[i], sizeof(platform_DTO), &socket_is_closed);
    }
}

void ProtocolServer::sendScore(score_DTO score){
    std::lock_guard<std::mutex> lock(mutex);
    uint8_t protocol_name = 0x02;
    connection.sendall(&protocol_name, ONE_BYTE, &socket_is_closed);
    connection.sendall(&score, sizeof(score_DTO), &socket_is_closed);
}

void ProtocolServer::sendFinalScore(score_DTO score){
    std::lock_guard<std::mutex> lock(mutex);
    uint8_t protocol_name = 0x03;
    connection.sendall(&protocol_name, ONE_BYTE, &socket_is_closed);
    connection.sendall(&score, sizeof(score_DTO), &socket_is_closed);
}

void ProtocolServer::shutDown() {
    if (!socket_is_closed) {
        connection.shutdown(SHUT_DOWN_TWO);
    }
}

ProtocolServer::~ProtocolServer() { connection.close(); }
