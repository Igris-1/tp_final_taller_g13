#pragma once

#include <cstdint>
#include <string>
#include "protocol_client.h"


class Client {
private:
    ProtocolClient protocol;
    void move(int direction);

public:
    void run();
    Client(const char* host, const char* port);
};