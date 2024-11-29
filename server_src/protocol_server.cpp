#include "protocol_server.h"

#include <bitset>
#include <cstdint>
#include <iostream>

#include <arpa/inet.h>
#include <string.h>

#include "../common_src/liberror.h"
#include "../common_src/translator_actions.h"

#include "duck_DTO.h"

ProtocolServer::ProtocolServer(Socket&& client):
        connection(std::move(client)), socket_is_closed(false) {}

bool ProtocolServer::socket_closed() { return socket_is_closed; }

action_t ProtocolServer::receive_action() {
    try {
        uint8_t code;
        action_t action;

        uint16_t action_16bits;
        connection.recvall(&action_16bits, sizeof(uint16_t), &socket_is_closed);
        TranslatorActions translator;
        translator.translate_flags(action_16bits, action.left, action.right, action.up, action.down,
                                   action.stop_right, action.stop_left, action.jump,
                                   action.stop_jump, action.press_action_button,
                                   action.unpress_action_button, action.press_pick_up_button,
                                    action.press_throw_button, action.press_crouch_button, action.unpress_crouch_button, action.press_look_up_button, action.unpress_look_up_button);
        connection.recvall(&action.player_id, sizeof(uint8_t), &socket_is_closed);
        return action;
    } catch (const LibError& e) {
        socket_is_closed = true;
        throw;
    }
}

int ProtocolServer::receive_number() {
    uint8_t buffer;
    connection.recvall(&buffer, sizeof(uint8_t), &socket_is_closed);
    return buffer;
}

/*void ProtocolServer::send_(){
    uint8_t code2 = 0x05;
    ss.sendall(&code2, 1, &aux);
}*/

void ProtocolServer::sendGameInfo(game_snapshot_t game_snapshot) {
    std::lock_guard<std::mutex> lock(mutex);
    uint8_t protocol_name = 0x01;
    connection.sendall(&protocol_name, sizeof(uint8_t), &socket_is_closed);

    connection.sendall(&game_snapshot.ducks_len, sizeof(uint8_t), &socket_is_closed);
    for (uint8_t i = 0; i < game_snapshot.ducks_len; i++) {
        connection.sendall(&game_snapshot.ducks[i], sizeof(duck_DTO), &socket_is_closed);
    }

    connection.sendall(&game_snapshot.bullets_len, sizeof(uint16_t), &socket_is_closed);
    for (uint16_t i = 0; i < game_snapshot.bullets_len; i++) {
        connection.sendall(&game_snapshot.bullets[i], sizeof(bullet_DTO), &socket_is_closed);
    }
    connection.sendall(&game_snapshot.weapons_len, sizeof(uint16_t), &socket_is_closed);
    for (uint16_t i = 0; i < game_snapshot.weapons_len; i++) {
        connection.sendall(&game_snapshot.weapons[i], sizeof(weapon_DTO), &socket_is_closed);
    }
    connection.sendall(&game_snapshot.boxes_len, sizeof(uint16_t), &socket_is_closed);
    for (uint16_t i = 0; i < game_snapshot.boxes_len; i++) {
        connection.sendall(&game_snapshot.boxes[i], sizeof(box_DTO), &socket_is_closed);
    }
    connection.sendall(&game_snapshot.sounds, sizeof(sounds_DTO), &socket_is_closed);
}

void ProtocolServer::sendGameStartInfo(map_structure_t map_structure) {
    std::lock_guard<std::mutex> lock(mutex);
    uint8_t protocol_name = 0x00;
    connection.sendall(&protocol_name, sizeof(uint8_t), &socket_is_closed);
    connection.sendall(&map_structure.width, sizeof(uint16_t), &socket_is_closed);
    connection.sendall(&map_structure.height, sizeof(uint16_t), &socket_is_closed);
    connection.sendall(&map_structure.platforms_len, sizeof(uint16_t), &socket_is_closed);
    for (int i = 0; i < map_structure.platforms_len; i++) {
        connection.sendall(&map_structure.platforms[i], sizeof(platform_DTO), &socket_is_closed);
    }
}

void ProtocolServer::sendScore(score_DTO score) {
    std::lock_guard<std::mutex> lock(mutex);
    uint8_t protocol_name = 0x02;
    connection.sendall(&protocol_name, sizeof(uint8_t), &socket_is_closed);
    connection.sendall(&score, sizeof(score_DTO), &socket_is_closed);
}

void ProtocolServer::sendFinalScore(score_DTO score) {
    std::lock_guard<std::mutex> lock(mutex);
    uint8_t protocol_name = 0x03;
    connection.sendall(&protocol_name, sizeof(uint8_t), &socket_is_closed);
    connection.sendall(&score, sizeof(score_DTO), &socket_is_closed);
}

void ProtocolServer::shutDown() {
    if (!socket_is_closed) {
        connection.shutdown(SHUT_RDWR);
    }
}

// Move Constructor
ProtocolServer::ProtocolServer(ProtocolServer&& other) noexcept:
        connection(std::move(other.connection)), socket_is_closed(other.socket_is_closed) {
    // No need to move the mutex, as std::mutex is not moveable
    other.socket_is_closed = true;  // Mark the old instance as "closed"
}

// Move Assignment Operator
ProtocolServer& ProtocolServer::operator=(ProtocolServer&& other) noexcept {
    if (this != &other) {
        // Lock the mutexes to ensure thread safety during the move
        std::lock_guard<std::mutex> lock(mutex);
        std::lock_guard<std::mutex> other_lock(other.mutex);

        // Move resources
        connection = std::move(other.connection);
        socket_is_closed = other.socket_is_closed;

        // Reset the source object
        other.socket_is_closed = true;  // Mark the old instance as "closed"
    }
    return *this;
}

ProtocolServer::~ProtocolServer() { connection.close(); }
