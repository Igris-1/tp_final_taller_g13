#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "../common_src/queue.h"
#include "../common_src/socket.h"

#include "acceptor_thread.h"
#include "client_handler.h"
#include "game_thread.h"
#include "thread_safe_list.h"

class Server {
private:
    const char* port;
    Queue<CommandInfo*> receiverQueue = Queue<CommandInfo*>(QUEUE_MAX_SIZE);
    ThreadSafeList<ClientHandler>* clientHandlerQueues = nullptr;

    void run();

public:
    explicit Server(const char* port);
    ~Server();
};
