#pragma once

#include "../common_src/game_snapshot_t.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"

#include "protocol_server.h"
#include "receiver_thread.h"
#include "sender_thread.h"

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
    void send_map(map_structure_t map);
    bool is_alive();
    ~ClientHandler();
};
