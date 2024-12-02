
#ifndef USABLE_MAPS_FINDER_H
#define USABLE_MAPS_FINDER_H

#include <cstdint>
#include <iostream>
#include "../common_src/socket.h"
#include <vector>

#define ONE_BYTE 1
#define TWO_BYTES 2


class UsableMapsFinder {
private:
    Socket socket;
    bool socket_is_closed = false;

public:
    UsableMapsFinder(const char* host, const char* port);
    ~UsableMapsFinder();
    void run();
    void stop();  // quizas no hace falta
    std::vector<std::string> ask_for_maps();
};


#endif