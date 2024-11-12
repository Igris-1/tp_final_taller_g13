#pragma once

#include "../common_src/socket.h"
#include <string>
#include <cstdint>
#include <mutex>
#include "game_snapshot_t.h"
#include "../common_src/action_t.h"


class ProtocolServer {

private:
    Socket connection;
    bool socket_is_closed;
    std::mutex mutex;

public:
    ProtocolServer(Socket&& client);

    action_t receive_action();

    int receive_number_of_players();

    bool socket_closed();

    void shutDown();

    void sendGameInfo(game_snapshot_t game_snapshot);

    void sendGameStartInfo(map_structure_t map_structure);
    
    ~ProtocolServer();
};
