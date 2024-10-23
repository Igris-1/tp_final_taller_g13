#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include <string>
#include <vector>

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "ListOfClientsMonitor.h"

#include "../common_src/game_snapshot.h"
#include "duck.h"
#include "client_handler.h"

/*
class GameThread: public Thread {
private:
    Duck duck;
    //ListOfClientsMonitor<action_t>* clientHandlerQueues;
    //Queue<CommandInfo*>& receiverQueue;

    void send_snapshots(action_t gs);
    void pickUpBox(const std::string& name, int box_id);
    void move_duck(int amount);
    void execute_commands();
    void run() override;

public:
    explicit GameThread(Queue<action_t>& receiverQueue,
                        ThreadSafeList<ClientHandler>* clientHandlerQueues);
};
*/
#endif