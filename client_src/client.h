#ifndef CLIENT_H
#define CLIENT_H

#include <cstdint>
#include <string>
#include "../common_src/socket.h"
#include "protocol_client.h"


class Client {
private:
    ProtocolClient protocol;
    void command (char pressed_key);
    game_snapshot_t get_snapshot();

public:
    void run();
    Client(const char* host, const char* port);
};

#endif
