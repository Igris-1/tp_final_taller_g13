#pragma once
#include <string>

#include "socket.h"
#include "string"


class Protocol {
private:
    Socket socket;
    bool socket_is_closed;

public:
    explicit Protocol(Socket&& socket);
    bool socket_closed();

    void kill_socket();

    ~Protocol();
};
