#pragma once

#include "../common_src/socket.h"
#include <string>
#include <cstdint>
#include "game_snapshot_t.h"
#include "../common_src/action_t.h"

class ProtocolServer {

private:
    Socket connection;
    bool socket_is_closed;

public:
    ProtocolServer(Socket&& client);

    action_t receive_action();

    bool socket_closed();

    void shutDown();

    void sendGameInfo(game_snapshot_t game_snapshot);

    ~ProtocolServer();
};
