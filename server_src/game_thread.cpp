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
#define SLEEP_TIME 200000

GameThread::GameThread(Queue<std::shared_ptr<Action>>& gameQueue, ListOfClientsMonitor& clients):
        game(50,50), gameQueue(gameQueue), clients(clients) {
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
        // action_t action = c_action.action;
        // if (action.right){
        //     std::cout << "Moving right" << std::endl;
        //     Position pos(1,0);
        //     game.move_duck(c_action.id, pos);
        // }
        // if (action.left){
        //     std::cout << "Moving left" << std::endl;
        //     Position pos(-1,0);
        //     game.move_duck(c_action.id, pos);
        // }
        c_action->execute(game);
    }
}

void GameThread::run() {

    while (_keep_running) {
        try {
            execute_commands();

        } catch (const ClosedQueue& e) {
            stop();
        }

        send_snapshots();

        usleep(SLEEP_TIME);
    }
}