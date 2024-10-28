#include "client.h"
#include <iostream>
#include "../common_src/action_t.h"
#include "../common_src/game_snapshot_t.h"

#define EXIT_CODE "q"

Client::Client(const char* host, const char* port)
        : protocol(Socket(host, port)){
            run();
        }

void Client::move(int direction) {
    action_t action;
    if (direction == 0) {
        action.left = true;
    } else {
        action.right = true;
    }
    protocol.send_action(action);
    game_snapshot_t snapshot = protocol.read_snapshot();
    std::cout << "Hay " << snapshot.ducks_len << " patos" << std::endl;

    for (int i=0; i<snapshot.ducks_len; i++){
        duck_DTO duck = snapshot.ducks[i];
        std::cout << "El pato " << duck.duck_id << " esta en " << duck.x << " " << duck.y << std::endl;
    }
    
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