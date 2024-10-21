#pragma once

#include <cstdint>
#include <string>
#include "../common_src/protocol.h"


class Client {
private:
    Protocol protocol;
    void move(int direction);

public:
    void run();
    Client(const char* host, const char* port);
};