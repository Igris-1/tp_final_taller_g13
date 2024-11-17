#pragma once

#include <cstdint>
#include <mutex>
#include <string>

#include "../common_src/action_t.h"
#include "../common_src/socket.h"

#include "game_snapshot_t.h"


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

    void sendScore(score_DTO score);
    
    void sendFinalScore(score_DTO score);

    void sendGameStartInfo(map_structure_t map_structure);

    ~ProtocolServer();
};
