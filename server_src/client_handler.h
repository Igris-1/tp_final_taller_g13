#pragma once

#include "protocol_server.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"

#include "receiver_thread.h"
#include "sender_thread.h"
#include "../common_src/game_snapshot_t.h"

class ClientHandler {
private:
    ProtocolServer protocol;
    Queue<game_snapshot_t> senderQueue;
    SenderThread senderThread;
    ReceiverThread receiverThread;
    int clientID;

public:
    ClientHandler(Socket&& socket, Queue<std::shared_ptr<Action>>& gameQueue, int id);
    void push(game_snapshot_t gs);
    bool is_alive();
    ~ClientHandler();
};
