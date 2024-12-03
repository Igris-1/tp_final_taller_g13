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

#define DEFAULT_CONFIG "../configuration_yamls/default_config.yaml"
#define PRACTICE_MAP "../maps/practice_map.yaml"
#define PRACTICE_CONFIG "../configuration_yamls/practice_config.yaml"
#define ROUNDS_PER_CHECK 5
#define MAX_PLAYERS 2

class GameThread: public Thread {
private:
    Game* game;
    Queue<std::shared_ptr<Action>>& gameQueue;
    ListOfClientsMonitor& clients;
    int max_players = MAX_PLAYERS;
    int round_counter = ROUNDS_PER_CHECK;
    void send_snapshots();
    void send_game_score();
    void send_map();
    void send_endgame_score();
    void blocking_execute_commands();
    void send_instructions();
    void pickUpBox(const std::string& name, int box_id);
    void execute_commands();
    void run() override;
    void send_initial_info();
    std::string map_name = "default_map";

    bool practice_mode;

public:
    explicit GameThread(Queue<std::shared_ptr<Action>>& gameQueue, ListOfClientsMonitor& clients, bool practice_mode, int max_players);
    void set_map_name(const std::string& map_name);
};

#endif