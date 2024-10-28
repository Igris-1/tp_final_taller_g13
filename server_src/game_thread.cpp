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

GameThread::GameThread(Queue<action_t>& gameQueue):
        duck(1,1), gameQueue(gameQueue) {
    start();
}

void GameThread::move_duck(Position& position){
    duck.move_to(position);
}

void GameThread::execute_commands() {

    action_t action;

    while (gameQueue.try_pop(action)) {
        if (action.right){
            std::cout << "Moving right" << std::endl;
            Position pos(1,0);
            move_duck(pos);
        }
        if (action.left){
            std::cout << "Moving left" << std::endl;
            Position pos(-1,0);
            move_duck(pos);
        }
    }
}

void GameThread::run() {

    while (_keep_running) {
        try {
            execute_commands();

        } catch (const ClosedQueue& e) {
            stop();
        }
        

        usleep(SLEEP_TIME);
    }
}