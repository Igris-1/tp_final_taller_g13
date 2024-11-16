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

void GameThread::send_snapshots() {
    game_snapshot_t snapshot = game.get_snapshot();
    if (snapshot.ducks_len != 0) {
        clients.enqueue_snapshot(snapshot);
    }
}

void GameThread::send_game_score() {
    score_DTO score = game.get_score_DTO();

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
    game.add_weapon_on_map("cowboy", 50, 150);
    game.add_weapon_on_map("laser_rifle", 150, 150);
    game.add_weapon_on_map("laser_rifle", 250, 150);
    game.add_weapon_on_map("cowboy", 350, 150);
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
        game.respawner();
        if(game.check_if_round_finished()){
            this->round_counter--;
            if(this->round_counter == 0){
                send_game_score();
            }
            //game.reset_round();
            usleep(SLEEP_TIME);
            continue;
        }
        send_snapshots();

        usleep(SLEEP_TIME);
    }
}