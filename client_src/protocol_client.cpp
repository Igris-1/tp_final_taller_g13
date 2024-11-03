#include "protocol_client.h"
#include "../common_src/translator_actions.h"
#include <cstdint>
#include <vector>
#include <iostream>
#include <bitset>

#define ONE_BYTE 1
#define SHUT_DOWN_TWO 2


ProtocolClient::ProtocolClient(Socket&& client) 
        : connection(std::move(client)), socket_is_closed(false) {}

ProtocolClient::ProtocolClient(ProtocolClient&& protocol) noexcept
    : connection(std::move(protocol.connection)), 
      socket_is_closed(protocol.socket_is_closed) {}

void ProtocolClient::send_action(action_t& action) {

    TranslatorActions translator;
    uint16_t action_16bits = translator.create_flag(action.left, action.right, action.up, action.down, action.stop_right, action.stop_left, action.jump, action.stop_jump);
    connection.sendall(&action_16bits, 2, &socket_is_closed);
}

uint8_t ProtocolClient::read_number() {

    uint8_t buffer;

    connection.recvall(&buffer, sizeof(uint8_t), &socket_is_closed);

    return buffer;
}

bool ProtocolClient::socket_closed(){
    return socket_is_closed;
}

game_snapshot_t ProtocolClient::read_snapshot(){
    uint8_t n = read_number();
    duck_DTO duck;
    game_snapshot_t game_snapshot;
    game_snapshot.ducks_len = n;
    game_snapshot.ducks.resize(n);

    int cant = static_cast<int>(n);
    for (int i=0; i<cant; i++){
        connection.recvall(&duck, sizeof(duck_DTO), &socket_is_closed);
        game_snapshot.ducks[i] = duck; //deberia pasarse con move? para evitar copiar
    }

    return game_snapshot;
}

void ProtocolClient::shutDown() {
    if (!socket_is_closed) {
        connection.shutdown(SHUT_DOWN_TWO);
    }
}

ProtocolClient::~ProtocolClient(){
    connection.close();
}

