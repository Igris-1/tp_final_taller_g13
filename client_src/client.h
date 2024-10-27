#ifndef CLIENT_H
#define CLIENT_H

#include <cstdint>
#include <string>
#include "../common_src/socket.h"
#include "protocol_client.h"


class Client {
private:
    ProtocolClient protocol;
    void move(int direction);

public:
    void run();
    Client(const char* host, const char* port);
};

#endif
