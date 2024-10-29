#include "protocol_client.h"
#include <cstdint>
#include <vector>

#define ONE_BYTE 1
#define SHUT_DOWN_TWO 2


ProtocolClient::ProtocolClient(Socket&& client) 
        : connection(std::move(client)), socket_is_closed(false) {}

void ProtocolClient::send_action(action_t& action) {
    bool code;
    code = action.left;
    connection.sendall(&code, ONE_BYTE, &socket_is_closed);
    code = action.right;
    connection.sendall(&code, ONE_BYTE, &socket_is_closed);
    code = action.up;
    connection.sendall(&code, ONE_BYTE, &socket_is_closed);
    code = action.down;
    connection.sendall(&code, ONE_BYTE, &socket_is_closed);
}

int ProtocolClient::read_number() {

    uint8_t buffer;

    connection.recvall(&buffer, sizeof(uint8_t), &socket_is_closed);

    return buffer;
}

bool ProtocolClient::socket_closed(){
    return socket_is_closed;
}

duck_DTO ProtocolClient::read_duck(){
    
    duck_DTO buffer;

    connection.recvall(&buffer, sizeof(uint8_t), &socket_is_closed);

    return buffer;
}

game_snapshot_t ProtocolClient::read_snapshot(){
    int n = read_number();
    duck_DTO duck;
    game_snapshot_t game_snapshot;
    game_snapshot.ducks_len = n;
    for (int i=0; i<n;i++){
        connection.recvall(&duck, sizeof(duck_DTO), &socket_is_closed);
        game_snapshot.ducks[i] = duck;
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
