#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include <string>
#include <vector>

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "list_of_clients_monitor.h"

#include "game_model/duck.h"
#include "client_handler.h"
#include "client_action_t.h"
#include "game_model/game.h"
#include "action.h"

class GameThread: public Thread {
private:
    Game game;
    Queue<std::shared_ptr<Action>>& gameQueue;
    ListOfClientsMonitor& clients;
    
    void send_snapshots();
    void pickUpBox(const std::string& name, int box_id);
    void move_duck(Position& position);
    void execute_commands();
    void run() override;

public:
    explicit GameThread(Queue<std::shared_ptr<Action>>& gameQueue, ListOfClientsMonitor& clients);
};

#endif