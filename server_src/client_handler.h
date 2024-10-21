#pragma once

#include "../common_src/command.h"
#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"

#include "receiver_thread.h"
#include "sender_thread.h"

class ClientHandler {
private:
    Protocol protocol;
    Queue<Command*> senderQueue;
    SenderThread senderThread;
    ReceiverThread receiverThread;

public:
    ClientHandler(Socket&& socket, Queue<CommandInfo*>& receiverQueue);
    void push(Command* command);
    bool is_alive();
    ~ClientHandler();
};
