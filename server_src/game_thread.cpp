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

// void GameThread::send_initial_info(){

// }

void GameThread::run() {    
    
    for(int i = 0; i<819; i++){
        game.add_invalid_position(Position(i,440));
    }
    for(int i = 0; i<499; i++){
        game.add_invalid_position(Position(790,i));
    }
    ////no deberia hasta q haya un pato
    for(int i = 0; i<100; i++){
        game.add_new_platform(Position(i,280));
    }

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
       
        usleep(SLEEP_TIME);
        send_snapshots();
    }
}