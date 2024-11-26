#include "protocol_client.h"

#include <bitset>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../common_src/duck_DTO.h"
#include "../common_src/translator_actions.h"

#include "message.h"

#define ONE_BYTE 1
#define TWO_BYTES 2
#define SHUT_DOWN_TWO 2


ProtocolClient::ProtocolClient(Socket&& client):
        connection(std::move(client)), socket_is_closed(false) {}

ProtocolClient::ProtocolClient(ProtocolClient&& protocol) noexcept:
        connection(std::move(protocol.connection)), socket_is_closed(protocol.socket_is_closed) {}

void ProtocolClient::send_number(int number) {
    uint8_t num = static_cast<uint8_t>(number);
    connection.sendall(&num, ONE_BYTE, &socket_is_closed);
}


void ProtocolClient::send_action(action_t& action) {

    TranslatorActions translator;
    uint16_t action_16bits = translator.create_flag(
            action.left, action.right, action.up, action.down, action.stop_right, action.stop_left,
            action.jump, action.stop_jump, action.press_action_button, action.unpress_action_button,
            action.press_pick_up_button, action.unpress_pick_up_button, action.press_throw_button);
    connection.sendall(&action_16bits, TWO_BYTES, &socket_is_closed);
    connection.sendall(&action.player_id, ONE_BYTE, &socket_is_closed);
}

uint8_t ProtocolClient::read_number() {

    uint8_t buffer;
    connection.recvall(&buffer, sizeof(uint8_t), &socket_is_closed);
    return buffer;
}

uint16_t ProtocolClient::read_long_number() {
    // endianness?
    uint16_t buffer;

    connection.recvall(&buffer, sizeof(uint16_t), &socket_is_closed);

    return buffer;
}

void ProtocolClient::receive_games(int size, Message& message) {
    std::vector<games_DTO> available_games;
    available_games.resize(size);
    for (int i = 0; i < size; i++) {
        games_DTO game;
        connection.recvall(&game, sizeof(games_DTO), &socket_is_closed);
        available_games[i] = game;
    }
    message.set_games(available_games);
}

bool ProtocolClient::socket_closed() { return socket_is_closed; }

map_structure_t ProtocolClient::receive_map() {
    map_structure_t map;
    uint16_t n = read_long_number();
    platform_DTO platform;
    map.platforms_len = n;
    map.platforms.resize(n);
    for (int i = 0; i < n; i++) {
        connection.recvall(&platform, sizeof(platform_DTO), &socket_is_closed);
        map.platforms[i] = platform;
    }
    return map;
}

game_snapshot_t ProtocolClient::read_snapshot() {

    uint8_t n = read_number();
    duck_DTO duck;
    game_snapshot_t game_snapshot;
    game_snapshot.ducks_len = n;
    game_snapshot.ducks.resize(n);

    int number_of_ducks = static_cast<int>(n);
    for (int i = 0; i < number_of_ducks; i++) {
        connection.recvall(&duck, sizeof(duck_DTO), &socket_is_closed);
        game_snapshot.ducks[i] = duck;
    }
    uint16_t m = read_long_number();
    bullet_DTO bullet;
    game_snapshot.bullets_len = m;
    game_snapshot.bullets.resize(m);
    int number_of_bullets = static_cast<int>(m);
    for (int i = 0; i < number_of_bullets; i++) {
        connection.recvall(&bullet, sizeof(bullet_DTO), &socket_is_closed);
        game_snapshot.bullets[i] = bullet;
    }
    m = read_long_number();
    weapon_DTO weapon;
    game_snapshot.weapons_len = m;
    game_snapshot.weapons.resize(m);
    int number_of_weapons = static_cast<int>(m);
    for (int i = 0; i < number_of_weapons; i++) {
        connection.recvall(&weapon, sizeof(weapon_DTO), &socket_is_closed);
        game_snapshot.weapons[i] = weapon;
    }
    m = read_long_number();
    box_DTO box;
    game_snapshot.boxes_len = m;
    game_snapshot.boxes.resize(m);
    int number_of_boxes = static_cast<int>(m);
    for (int i = 0; i < number_of_boxes; i++) {
        connection.recvall(&box, sizeof(box_DTO), &socket_is_closed);
        game_snapshot.boxes[i] = box;
    }
    return game_snapshot;
}

score_DTO ProtocolClient::read_score() {
    score_DTO score;
    connection.recvall(&score, sizeof(score_DTO), &socket_is_closed);
    return score;
}


void ProtocolClient::shutDown() {
    if (!socket_is_closed) {
        connection.shutdown(SHUT_DOWN_TWO);
    }
}

ProtocolClient::~ProtocolClient() { connection.close(); }
