#include "game_thread.h"

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <unistd.h>

#include "receiver_thread.h"
#include "sender_thread.h"

#define SPEED_MOVEMENTS 10 
#define SLEEP_TIME 40000


GameThread::GameThread(Queue<std::shared_ptr<Action>>& gameQueue, ListOfClientsMonitor& clients):
        game(500, 820), gameQueue(gameQueue), clients(clients) {
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
    if (instruction.gs.ducks_len != 0) {
        clients.enqueue_instruction(instruction);
    }
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


void GameThread::run() {
    game.add_new_platform(Hitbox(0, 350, 192, 16));
    game.add_new_platform(Hitbox(350, 240, 469, 16));
    game.add_new_platform(Hitbox(500, 100, 240, 16));
    game.add_new_platform(Hitbox(0, 100, 230, 16));

    game.add_invalid_position(Hitbox(0, 430, 820, 2));

    //metodo_nuevo();

    // game.add_weapon_on_map("cowboy", 50, 150);
    // game.add_weapon_on_map("laser_rifle", 150, 150);
    // game.add_weapon_on_map("laser_rifle", 250, 150);
    // game.add_weapon_on_map("cowboy", 350, 150);

    // game.add_spawn_position(192, 1);
    // game.add_spawn_position(150, 150);
    game.add_spawn_position(250, 150);
    game.add_spawn_position(350, 150);

    
    clients.send_map(game.get_map_structure());

    while (_keep_running) {
        try {
            execute_commands();
            

        } catch (const ClosedQueue& e) {
            stop();
        }

        game.continue_vertical_movements(SPEED_MOVEMENTS);
        game.continue_horizontal_movements(SPEED_MOVEMENTS);
        game.keep_shooting();
        game.random_weapon_spawn();
        //game.respawner(); dejar comentado, si lo descomentas o borras, sos gay.

        
        if(game.check_if_round_finished()){
            if (game.check_if_winner()){
                std::cout << "Game finished" << std::endl;
                send_endgame_score();   
            }
            this->round_counter--;
            if(this->round_counter == 0){
                std::cout << "5th round finished" << std::endl;
                send_game_score();
            }
            game.reset_round();
            usleep(SLEEP_TIME);
            continue;
        }
        send_snapshots();

        usleep(SLEEP_TIME);
    }
}