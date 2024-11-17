#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "client_handler.h"
#include "game_thread.h"

class Server {
private:
    const char* port;

public:
    explicit Server(const char* port, int start_size_of_games);
    void start(int start_size_of_games);
    ~Server();
};
