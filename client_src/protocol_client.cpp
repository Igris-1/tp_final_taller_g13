#include "protocol_client.h"

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

bool ProtocolClient::socket_closed(){
    return socket_is_closed;
}

bool ProtocolClient::read_snapshot() {
    bool code;
    connection.recvall(&code, ONE_BYTE, &socket_is_closed);
}

void ProtocolClient::shutDown() {
    if (!socket_is_closed) {
        connection.shutdown(SHUT_DOWN_TWO);
    }
}

ProtocolClient::~ProtocolClient(){
    connection.close();
}

