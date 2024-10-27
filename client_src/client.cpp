#include "client.h"
#include <iostream>
#include "../common_src/action_t.h"

#define EXIT_CODE "q"

Client::Client(const char* host, const char* port)
        : protocol(Socket(host, port)){
            run();
        }

void Client::move(int direction) {
    action_t action;
    std::cout << "Moving ";
    if (direction == 0) {
        std::cout << "left" << std::endl;
        action = action_t(true, false, false, false);
    } else {
        std::cout << "right" << std::endl;
        action = action_t(false, true, false, false);
    }
    protocol.send_action(action);
}

void Client::run() {

    bool socket_closed = protocol.socket_closed();

    while (!socket_closed) {
        std::string orders;
        std::getline(std::cin, orders);

        if (orders == EXIT_CODE) {
            break;
        }

        if (orders == "a") {
            move(0);
        } else if (orders == "d") {
            move(1);
        }

        socket_closed = protocol.socket_closed();
    }
}