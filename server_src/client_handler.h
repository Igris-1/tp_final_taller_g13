#pragma once

#include "ProtocolServer.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"

#include "receiver_thread.h"
#include "sender_thread.h"
#include "../common_src/game_snapshot.h"

class ClientHandler {
private:
    ProtocolServer protocol;
    Queue<game_snapshot_t> senderQueue;
    SenderThread senderThread;
    ReceiverThread receiverThread;

public:
    ClientHandler(Socket&& socket, Queue<action_t>& receiverQueue);
    void push(game_snapshot_t gs);
    bool is_alive();
    ~ClientHandler();
};
