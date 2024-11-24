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

    try {
        //                          x, y, width, height
        game.add_new_platform(Hitbox(0, 200, 200, 16));
        game.add_new_platform(Hitbox(25, 350, 450, 16));
        //game.add_new_platform(Hitbox(25, 310, 450, 16));//esta es nueva
        game.add_new_platform(Hitbox(40, 420, 600, 16));
        game.add_new_platform(Hitbox(0, 510, 300, 16));
        game.add_new_platform(Hitbox(580, 200, 200, 16));
        game.add_new_platform(Hitbox(600, 350, 400, 16));
        game.add_new_platform(Hitbox(200, 600, 100, 16));
        game.add_new_platform(Hitbox(0, 600, 300, 16));
        //game.add_new_platform(Hitbox(230, 200, 300, 16));

        game.add_box(Hitbox(500, 500, 50, 50));

        game.add_new_platform(Hitbox(0, 654, 700, 16));
        game.add_new_platform(Hitbox(700, 654, 465, 16));

        game.add_item_on_map("helmet", 0, 0);
        game.add_item_on_map("armor", 600, 555);
    } catch (const GameError& e) {
        std::cerr << e.what() << std::endl;
    }catch (MapError& e) {
        std::cerr << "Map Error " << e.what() << std::endl;
    }catch (...) {
        std::cerr << "Error desconocido" << std::endl;
    }

    game.add_spawn_position(15, 180);
    game.add_spawn_position(30, 300);
    game.add_spawn_position(500, 350);
    game.add_spawn_position(650, 490);

    game.random_weapon_spawn(false);
    int start_flag = 0;

    for (int i = 0; i < 4; i++) {
        blocking_execute_commands();
    }

    while (this->game.get_duck_DTO_list().size() < 4) {
        std::cout << "Waiting for players to join" << std::endl;
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
        game.random_weapon_spawn(true);
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