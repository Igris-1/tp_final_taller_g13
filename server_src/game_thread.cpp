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
        game(820,500), gameQueue(gameQueue), clients(clients) {
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

    while (_keep_running) {
        try {
            execute_commands();

        } catch (const ClosedQueue& e) {
            stop();
        }

        game.continue_movements();
        send_snapshots();
        usleep(SLEEP_TIME);
    }
}