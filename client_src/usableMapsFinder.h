
#ifndef USABLE_MAPS_FINDER_H
#define USABLE_MAPS_FINDER_H

#include <cstdint>
#include <iostream>
#include "../common_src/socket.h"
#include <vector>
#include "protocol_client.h"


class UsableMapsFinder {
private:
    ProtocolClient protocol;
    bool socket_is_closed = false;

public:
    UsableMapsFinder(const char* host, const char* port);
    ~UsableMapsFinder();
    std::vector<std::string> ask_for_maps();
};


#endif