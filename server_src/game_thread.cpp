#include "game_thread.h"

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

#include "../configuration_yamls/game_config.h"

#include "receiver_thread.h"
#include "sender_thread.h"

#define LOOP_TIME 40000

GameThread::GameThread(Queue<std::shared_ptr<Action>>& gameQueue, ListOfClientsMonitor& clients, bool practice_mode, int max_players):
        game(nullptr), gameQueue(gameQueue), clients(clients), practice_mode(practice_mode){
    this->max_players = max_players;
    start();
}

void GameThread::send_snapshots() {
    instruction_for_client_t instruction;
    instruction.id = 1;
    instruction.gs = game->get_snapshot();
    clients.enqueue_instruction(instruction);
}

void GameThread::send_map() {
    instruction_for_client_t instruction;
    instruction.id = 0;
    instruction.map = game->get_map_structure();
    clients.enqueue_instruction(instruction);
}

void GameThread::send_game_score() {
    instruction_for_client_t instruction;
    instruction.id = 2;
    instruction.score = game->get_score_DTO();
    clients.enqueue_instruction(instruction);
}

void GameThread::send_endgame_score() {
    instruction_for_client_t instruction;
    instruction.id = 3;
    instruction.score = game->get_score_DTO();
    clients.enqueue_instruction(instruction);
}

void GameThread::execute_commands() {
    std::shared_ptr<Action> c_action;
    while (gameQueue.try_pop(c_action)) {
        c_action->execute((*this->game));
    }
}

void GameThread::blocking_execute_commands() {
    std::shared_ptr<Action> c_action = gameQueue.pop();
    c_action->execute((*this->game));
}

void GameThread::run() {
    std::string path_map = "../maps/default_map.yaml";
    std::string path_config = "../configuration_yamls/default_config.yaml";
    if(this->practice_mode){
        path_map = "../maps/practice_map.yaml";
        path_config = "../configuration_yamls/practice_config.yaml";
    }

    GameConfig game_config(path_map, path_config);

    Game aux(game_config);
    this->game = &aux;
    this->game->load_configuration(game_config);

    // spawnea armas para el comienzo de la partida
    this->game->random_item_spawn(false, this->practice_mode);

    for (int i = 0; i < this->max_players; i++) {
        blocking_execute_commands();
    }

    while (this->game->get_duck_DTO_list().size() < this->max_players) {
        std::this_thread::sleep_for(std::chrono::microseconds(LOOP_TIME));
    }
    send_map();

    while (_keep_running) {
        auto start_time = std::chrono::steady_clock::now();
        this->game->keep_using_item();
        try {
            execute_commands();

        } catch (const ClosedQueue& e) {
            stop();
        }

        this->game->continue_vertical_movements();
        this->game->continue_horizontal_movements();
        this->game->random_item_spawn(true, this->practice_mode);
        
        if (this->game->check_if_round_finished()) {

            send_snapshots();
            this->game->continue_vertical_movements();
            this->game->continue_horizontal_movements();
            send_snapshots();
            this->game->continue_vertical_movements();
            this->game->continue_horizontal_movements();
            send_snapshots();
            if (this->game->check_if_winner() && !this->practice_mode) {
                send_endgame_score();
                this->_is_alive = false;
                return;
            }
            if(!this->practice_mode){
                this->round_counter--;
            }
            if (this->round_counter == 0) {
                send_game_score();
                this->round_counter = 5;
                // usleep(1000000);
            }
            this->game->reset_round();
            std::this_thread::sleep_for(std::chrono::microseconds(LOOP_TIME));
            continue;
        }
        send_snapshots();
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_time =
                std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time)
                        .count();
        int remaining_time = LOOP_TIME - elapsed_time;
        std::this_thread::sleep_for(std::chrono::microseconds(remaining_time));
    }
}
