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
        game(), clientHandlerQueues(clientHandlerQueues), receiverQueue(receiverQueue) {

    start();
}


void GameThread::sendCommands(Command* command) {
    clientHandlerQueues->for_each([command](ClientHandler& handler) {
        Command* commands = command->clone();
        handler.push(commands);  // push here cause it's unlikely the queue is full
    });
    delete command;
}

void GameThread::pickUpBox(const std::string& name, int box_id) {
    try {
        int reward_id = game.pickUpBox(box_id);
        if (reward_id) {
            std::string reward = game.getReward(reward_id);
            std::cout << name.data() << " picked up a " << reward << std::endl;

            Command* command = new ReadPickUpCommand(name, reward_id);


            sendCommands(command);
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GameThread::move_duck(int duck_id, int amount){
    duck.move(int amount, 0);
}

void GameThread::execute_commands() {

    CommandInfo* command_info;

    while (receiverQueue.try_pop(command_info) && command_info) {
        action_t action = command_info->get_action();
        if (action == LEFT){
            int duck_id = command_info->get_duck_id();
            move_duck(duck_id, -1);
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