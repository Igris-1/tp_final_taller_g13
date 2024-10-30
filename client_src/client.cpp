#include "client.h"
#include <iostream>
#include "../common_src/action_t.h"
#include "../common_src/game_snapshot_t.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#define EXIT_CODE "q"

Client::Client(const char* host, const char* port)
        : protocol(Socket(host, port)){
            run();
        }

//levantar imagenes en cada itreracion del juego <-- NO HACERLO
//HAY QUE CARGAR IMAGENES FUERA DE LOOP
// NO DIBUJAR COSAS QNO ESTAN EN LA PANTALLA
game_snapshot_t Client::get_snapshot(){

    game_snapshot_t snapshot = protocol.read_snapshot();
    std::cout << "Hay " << snapshot.ducks_len << " patos" << std::endl;

    for (int i=0; i<snapshot.ducks_len; i++){
        duck_DTO duck = snapshot.ducks[i];
        std::cout << "El pato " << duck.duck_id << " esta en " << duck.x << " " << duck.y << std::endl;
    }

    return snapshot;// despues se lo pasa al front
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

void Client::run() {

    bool socket_closed = protocol.socket_closed();

    while (!socket_closed) {
        std::string orders;
        std::getline(std::cin, orders);

        if (orders == EXIT_CODE) {
            break;
        }

        command(orders[0]);
        game_snapshot_t snapshot = get_snapshot();

        socket_closed = protocol.socket_closed();
    }
}