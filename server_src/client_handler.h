#pragma once

#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"

#include "receiver_thread.h"
#include "sender_thread.h"
#include "../common_src/game_snapshot.h"

class ClientHandler {
private:
    Protocol protocol;
    Queue<GameSnapshot*> senderQueue;
    SenderThread senderThread;
    ReceiverThread receiverThread;

public:
    ClientHandler(Socket&& socket, Queue<CommandInfo*>& receiverQueue);
    void push(GameSnapshot* gs);
    bool is_alive();
    ~ClientHandler();
};
