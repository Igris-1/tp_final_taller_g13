#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include <string>
#include <vector>

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "actions/action.h"
#include "actions/client_action_t.h"
#include "game_model/duck.h"
#include "game_model/game.h"

#include "client_handler.h"
#include "list_of_clients_monitor.h"

class GameThread: public Thread {
private:
    Game* game;
    Queue<std::shared_ptr<Action>>& gameQueue;
    ListOfClientsMonitor& clients;
    int round_counter = 5;
    void send_snapshots();
    void send_game_score();
    void send_map();
    void send_endgame_score();
    void blocking_execute_commands();
    void send_instructions();
    void pickUpBox(const std::string& name, int box_id);
    // void move_duck(Position& position);
    void execute_commands();
    void run() override;
    void send_initial_info();

public:
    explicit GameThread(Queue<std::shared_ptr<Action>>& gameQueue, ListOfClientsMonitor& clients);
};

#endif