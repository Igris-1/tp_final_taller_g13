#include "game_thread.h"

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <unistd.h>

#include "receiver_thread.h"
#include "sender_thread.h"
#include "../configuration_yamls/parser_singleton.h"

#define SPEED_MOVEMENTS 10
#define SLEEP_TIME 40000

GameThread::GameThread(Queue<std::shared_ptr<Action>>& gameQueue, ListOfClientsMonitor& clients):
        game(768, 1366), gameQueue(gameQueue), clients(clients) {
    start();
}

// void GameThread::send_snapshots() {
//     game_snapshot_t snapshot = game.get_snapshot();
//     if (snapshot.ducks_len != 0) {
//         clients.enqueue_snapshot(snapshot);
//     }
// }

void GameThread::send_snapshots() {
    instruction_for_client_t instruction;
    instruction.id = 1;
    instruction.gs = game.get_snapshot();
    // if (instruction.gs.ducks_len != 0) {
    clients.enqueue_instruction(instruction);
    //}
}

void GameThread::send_map() {
    instruction_for_client_t instruction;
    instruction.id = 0;
    instruction.map = game.get_map_structure();
    clients.enqueue_instruction(instruction);
}

// void GameThread::send_instructions() {
//     instruction_for_client_t instruction;
//     instruction.id = game.get_message_type();
//     instruction.gs = game.get_snapshot();
//     clients.enqueue_instruction(instruction);
// }

void GameThread::send_game_score() {
    instruction_for_client_t instruction;
    instruction.id = 2;
    instruction.score = game.get_score_DTO();
    clients.enqueue_instruction(instruction);
}

void GameThread::send_endgame_score() {
    instruction_for_client_t instruction;
    instruction.id = 3;
    instruction.score = game.get_score_DTO();
    clients.enqueue_instruction(instruction);
}

void GameThread::execute_commands() {
    std::shared_ptr<Action> c_action;
    while (gameQueue.try_pop(c_action)) {
        c_action->execute(game);
    }
}

void GameThread::blocking_execute_commands() {
    std::shared_ptr<Action> c_action = gameQueue.pop();
    c_action->execute(game);
}


void GameThread::run() {
    // singleton del parser de yaml
    ParserYAML* parser =  ParserSingleton::get_instance();
    parser->load_files("../configuration_yamls/default_map_config.yaml", "../configuration_yamls/default_config.yaml");
    
    // pide todas las plataformas y las agrega al juego
    std::vector<std::tuple<int, int, int, int>> aux_tuple_of_four =  parser->get_map_structure("platforms");
    for(auto& platform : aux_tuple_of_four){
        game.add_new_platform(Hitbox(std::get<0>(platform), std::get<1>(platform), std::get<2>(platform), std::get<3>(platform)));
    }

    // pide todas las cajas y las agrega al juego
    std::vector<std::tuple<int, int>> aux_tuple_of_two =  parser->get_spawn_points("boxes");
    for(auto& box : aux_tuple_of_two){
        game.add_box(Hitbox(std::get<0>(box), std::get<1>(box), 50, 50));
    }

    // pide las posiciones donde estaran los spawns de armas
    aux_tuple_of_two =  parser->get_spawn_points("weapons");
    for(auto& weapon : aux_tuple_of_two){
        game.add_spawn_position(std::get<0>(weapon), std::get<1>(weapon));
    }

    // pide las posiciones donde estaran los spawns de patos
    aux_tuple_of_two =  parser->get_spawn_points("ducks");
    for(auto& duck : aux_tuple_of_two){
        game.add_spawn_duck(std::get<0>(duck), std::get<1>(duck));
    } 

    // spawnea armas para el comienzo de la partida
    game.random_item_spawn(false);
    int start_flag = 0;

    for (int i = 0; i < 4; i++) {
        blocking_execute_commands();
    }

    while (this->game.get_duck_DTO_list().size() < 4) {
        usleep(SLEEP_TIME);
    }
    send_map();

    while (_keep_running) {
        game.keep_using_item();
        try {
            execute_commands();


        } catch (const ClosedQueue& e) {
            stop();
        }

        game.continue_vertical_movements(SPEED_MOVEMENTS);
        game.continue_horizontal_movements(SPEED_MOVEMENTS);
        game.random_item_spawn(true);
        // game.respawner(); dejar comentado, si lo descomentas o borras, sos gay.


        if (game.check_if_round_finished()) {
            send_snapshots();
            if (game.check_if_winner()) {
                send_endgame_score();
                this->_is_alive = false;
                return;
            }
            this->round_counter--;
            if (this->round_counter == 0) {
                send_game_score();
                this->round_counter = 5;
                // usleep(1000000);
            }
            game.reset_round();
            usleep(SLEEP_TIME);
            continue;
            usleep(SLEEP_TIME);
        }
        send_snapshots();

        usleep(SLEEP_TIME);
    }
}