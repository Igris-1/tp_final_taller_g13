#ifndef JOINABLE_GAMES_FINDER_H
#define JOINABLE_GAMES_FINDER_H

#include <vector>

#include "../common_src/socket.h"
#include "protocol_client.h"

class JoinableGamesFinder {
private:
    ProtocolClient protocol;
    bool socket_is_closed = false;

public:
    JoinableGamesFinder(const char* host, const char* port);
    ~JoinableGamesFinder();
    std::vector<games_DTO> ask_for_games();
};


#endif