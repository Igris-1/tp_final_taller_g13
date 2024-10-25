#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include <string>
#include <vector>

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "list_of_clients_monitor.h"

#include "../common_src/game_snapshot.h"
#include "game_model/duck.h"
#include "client_handler.h"




class GameThread: public Thread {
private:
    Duck duck;
    Queue<action_t>& gameQueue;

    void make_snapshots(action_t gs);
    void pickUpBox(const std::string& name, int box_id);
    void move_duck(Position& position);
    void execute_commands();
    void run() override;

public:
    explicit GameThread(Queue<action_t>& gameQueue);
};

#endif