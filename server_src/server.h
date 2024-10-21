#pragma once

#include <iostream>

class Server {
private:
    const char* port;
    void run();

public:
    explicit Server(const char* port);
};
