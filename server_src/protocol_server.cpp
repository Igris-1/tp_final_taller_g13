#include "protocol_server.h"

#include <bitset>
#include <cstdint>
#include <iostream>

#include <arpa/inet.h>
#include <string.h>

#include "../common_src/liberror.h"
#include "../common_src/translator_actions.h"

#include "../common_src/DTOs.h"

ProtocolServer::ProtocolServer(Socket&& client):
        connection(std::move(client)), socket_is_closed(false) {}

bool ProtocolServer::socket_closed() { return socket_is_closed; }

action_t ProtocolServer::receive_action() {
    try {
        uint8_t code;
        action_t action;
        uint16_t action_16bits;
        connection.recvall(&action_16bits, TWO_BYTES, &socket_is_closed);
        action_16bits = ntohs(action_16bits);
        TranslatorActions translator;
        translator.translate_flags(
                action_16bits, action.left, action.right, action.up, action.down, action.stop_right,
                action.stop_left, action.jump, action.stop_jump, action.press_action_button,
                action.unpress_action_button, action.press_pick_up_button,
                action.press_throw_button, action.press_crouch_button, action.unpress_crouch_button,
                action.press_look_up_button, action.unpress_look_up_button);
        connection.recvall(&action.player_id, ONE_BYTE, &socket_is_closed);
        return action;
    } catch (const LibError& e) {
        socket_is_closed = true;
        throw;
    }
}

int ProtocolServer::receive_number() {
    uint8_t buffer;
    connection.recvall(&buffer, ONE_BYTE, &socket_is_closed);
    return buffer;
}

void ProtocolServer::send_number(uint8_t& number) {
    uint8_t buffer = number;
    connection.sendall(&buffer, ONE_BYTE, &socket_is_closed);
}

void ProtocolServer::send_long_number(uint16_t& number) {
    uint16_t buffer = htons(number);
    connection.sendall(&buffer, TWO_BYTES, &socket_is_closed);
}

void ProtocolServer::sendGameInfo(game_snapshot_t game_snapshot) {
    
    uint8_t protocol_name = PROTOCOL_SEND_GAME_INFO;
    this->send_number(protocol_name);
    this->send_number(game_snapshot.ducks_len);
    for (uint8_t i = 0; i < game_snapshot.ducks_len; i++) {
        this->translator_dto.hton_duck_DTO(&game_snapshot.ducks[i]);
        connection.sendall(&game_snapshot.ducks[i], sizeof(duck_DTO), &socket_is_closed);
    }
    this->send_long_number(game_snapshot.bullets_len);
    for (uint16_t i = 0; i < game_snapshot.bullets_len; i++) {
        this->translator_dto.hton_bullet_DTO(&game_snapshot.bullets[i]);
        connection.sendall(&game_snapshot.bullets[i], sizeof(bullet_DTO), &socket_is_closed);
    }
    this->send_long_number(game_snapshot.weapons_len);
    for (uint16_t i = 0; i < game_snapshot.weapons_len; i++) {
        this->translator_dto.hton_weapon_DTO(&game_snapshot.weapons[i]);
        connection.sendall(&game_snapshot.weapons[i], sizeof(weapon_DTO), &socket_is_closed);
    }
    this->send_long_number(game_snapshot.boxes_len);
    for (uint16_t i = 0; i < game_snapshot.boxes_len; i++) {
        this->translator_dto.hton_box_DTO(&game_snapshot.boxes[i]);
        connection.sendall(&game_snapshot.boxes[i], sizeof(box_DTO), &socket_is_closed);
    }
    this->translator_dto.hton_sounds_DTO(&game_snapshot.sounds);
    connection.sendall(&game_snapshot.sounds, sizeof(sounds_DTO), &socket_is_closed);
}

void ProtocolServer::sendGameStartInfo(map_structure_t map_structure) {
    uint8_t protocol_name = PROTOCOL_SEND_GAME_START_INFO;
    this->send_number(protocol_name);
    this->send_long_number(map_structure.width);
    this->send_long_number(map_structure.height);
    this->send_long_number(map_structure.platforms_len);
    for (int i = 0; i < map_structure.platforms_len; i++) {
        this->translator_dto.hton_platform_DTO(&map_structure.platforms[i]);
        connection.sendall(&map_structure.platforms[i], sizeof(platform_DTO), &socket_is_closed);
    }
    this->send_long_number(map_structure.spawns_platforms_len);
    for (int i = 0; i < map_structure.spawns_platforms_len; i++) {
        this->translator_dto.hton_platform_DTO(&map_structure.spawns_platforms[i]);
        connection.sendall(&map_structure.spawns_platforms[i], sizeof(platform_DTO), &socket_is_closed);
    }
}

void ProtocolServer::sendScore(score_DTO score) {
    
    uint8_t protocol_name = PROTOCOL_SEND_SCORE;
    this->send_number(protocol_name);
    this->translator_dto.hton_score_DTO(&score);
    connection.sendall(&score, sizeof(score_DTO), &socket_is_closed);
}

void ProtocolServer::sendFinalScore(score_DTO score) {
    
    uint8_t protocol_name = PROTOCOL_SEND_FINAL_SCORE;
    this->send_number(protocol_name);
    this->translator_dto.hton_score_DTO(&score);
    connection.sendall(&score, sizeof(score_DTO), &socket_is_closed);
}

void ProtocolServer::shutDown() {
    if (!socket_is_closed) {
        connection.shutdown(SHUT_RDWR);
    }
}

ProtocolServer::ProtocolServer(ProtocolServer&& other) noexcept:
        connection(std::move(other.connection)), socket_is_closed(other.socket_is_closed) {
    other.socket_is_closed = true;
}

ProtocolServer& ProtocolServer::operator=(ProtocolServer&& other) noexcept {
    if (this != &other) {
        connection = std::move(other.connection);
        socket_is_closed = other.socket_is_closed;

        other.socket_is_closed = true;
    }
    return *this;
}

ProtocolServer::~ProtocolServer() { connection.close(); }
