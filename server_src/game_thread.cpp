#include "game_thread.h"

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <unistd.h>
#include "receiver_thread.h"
#include "sender_thread.h"
#include "../common_src/protocol_client.h"


#define BOX_RESPAWNED_TEXT "A new box has appeared"
#define SLEEP_TIME 200000

GameThread::GameThread(Queue<CommandInfo*>& receiverQueue,
                       ThreadSafeList<ClientHandler>* clientHandlerQueues):
        duck(0,4,4), clientHandlerQueues(clientHandlerQueues), receiverQueue(receiverQueue) {

    start();
}


void GameThread::send_snapshots(GameSnapshot* gs) {
    clientHandlerQueues->for_each([gs](ClientHandler& handler) {
        GameSnapshot* gss = gs->clone();
        handler.push(gss);  // push here cause it's unlikely the queue is full
    });
    delete gs;
}

void GameThread::move_duck(int amount){
    duck.move(amount, 0);
    GameSnapshot* gs = new GameSnapshot();
    SimpleDuck sduck = SimpleDuck((duck.get_pos()));
    gs->add_duck(sduck);
    send_snapshots(gs);
}

void GameThread::execute_commands() {

    CommandInfo* command_info;

    while (receiverQueue.try_pop(command_info) && command_info) {
        action_t action = command_info->get_action();
        if (action == LEFT){
            move_duck(-1);
            delete command_info;
        }
        if (action == RIGHT){
            move_duck(1);
            delete command_info;
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