#include "client.h"
#include <iostream>
#include "../common_src/action_t.h"
#include "../common_src/game_snapshot_t.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#define EXIT_CODE "q"

Client::Client(const char* host, const char* port)
    : protocol(Socket(host, port)),
      receiver_queue(),
      sender_queue(),
      receiver(protocol),
      sender(protocol, sender_queue) {
    run();
}

void Client::command(char pressed_key) {
    action_t action;
    if (pressed_key == 'a') {
        action.left = true;
    } else if (pressed_key == 'd') {
        action.right = true;
    }
    protocol.send_action(action);
}

Client::~Client() {
    protocol.shutDown();
    sender_queue.close();
    
    receiver.stop();
    sender.stop();

    receiver.join();
    sender.join();
}

void Client::run() {

    while (!protocol.socket_closed()) {
        std::string orders;
        std::getline(std::cin, orders);

        if (orders == EXIT_CODE) {
            break;
        }

        command(orders[0]);
    }
}