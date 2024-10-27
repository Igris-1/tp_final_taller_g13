#pragma once

#include "../common_src/socket.h"
#include <string>
#include <cstdint>
#include "../common_src/game_snapshot.h"
#include "game_snapshot_t.h"
#include "../common_src/action_t.h"

class ProtocolServer {

private:
    Socket connection;
    bool socket_is_closed;

public:
    ProtocolServer(Socket&& client);

    action_t read_action();

    bool socket_closed();

    void shutDown();

    ~ProtocolServer();
};
