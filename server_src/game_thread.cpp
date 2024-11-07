#include "game_thread.h"

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <unistd.h>
#include "receiver_thread.h"
#include "sender_thread.h"

#define BOX_RESPAWNED_TEXT "A new box has appeared"
#define SLEEP_TIME 40000

GameThread::GameThread(Queue<std::shared_ptr<Action>>& gameQueue, ListOfClientsMonitor& clients):
        game(500,820), gameQueue(gameQueue), clients(clients) {

    start();
}

void GameThread::send_snapshots(){
    game_snapshot_t snapshot = game.get_snapshot();
    if (snapshot.ducks_len!=0){
        clients.enqueue_snapshot(snapshot); 
    }
}

void GameThread::execute_commands() {
    std::shared_ptr<Action> c_action;
    while (gameQueue.try_pop(c_action)) {
        c_action->execute(game);
    }
}



void GameThread::run() {    
    
    game.add_new_platform(Hitbox(0,350,192,16));
    game.add_new_platform(Hitbox(350,240,469,16));
    game.add_new_platform(Hitbox(500,100,240,16));
    game.add_new_platform(Hitbox(0,100,230,16));

    game.add_invalid_position(Hitbox(0,430, 820, 2));
    
    clients.send_map(game.get_map_structure());
    while (_keep_running) {
        try {
            execute_commands();

        } catch (const ClosedQueue& e) {
            stop();
        }
        
        game.continue_horizontal_movements(10);
        game.continue_vertical_movements(10);
        //game.continue_bullets_movements(10);
        
        send_snapshots();
        usleep(SLEEP_TIME);
    }
}