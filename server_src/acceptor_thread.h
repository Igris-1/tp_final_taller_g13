#pragma once

#include <list>
#include <utility>
#include <vector>

#include "../common_src/liberror.h"
#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "client_handler.h"
#include "receiver_thread.h"
#include "sender_thread.h"
#include "thread_safe_list.h"

#define QUEUE_MAX_SIZE 200

class AcceptorThread: public Thread {
private:
    Socket& socket_server;
    Queue<CommandInfo*>& receiverQueue;
    ThreadSafeList<ClientHandler>* clientHandlerQueues;  // cppcheck-suppress unusedStructMember

    void reap_dead();
    void kill_clients();
    void run() override;

public:
    AcceptorThread(Socket& socket, Queue<CommandInfo*>& receiverQueue,
                   ThreadSafeList<ClientHandler>* clientHandlerQueues);
    ~AcceptorThread() override;
};
