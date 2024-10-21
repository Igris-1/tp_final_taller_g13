#include "protocol.h"

Protocol::Protocol(Socket&& socket): socket(std::move(socket)), socket_is_closed(false) {}

bool Protocol::socket_closed() { return socket_is_closed; }

void Protocol::kill_socket() {
    if (!socket_is_closed) {
        socket.shutdown(2);
    }
}

Protocol::~Protocol() { socket.close(); }