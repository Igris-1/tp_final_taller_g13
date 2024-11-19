#include <iostream>

#include "client.h"
#define ERROR -1
#define SUCCESS 0
#define REQUIRED_ARGC 4
#define HOST_ARG 1
#define PORT_ARG 2
#define LOCAL_PLAYERS 3


int main(int argc, const char* argv[]) {
    try {

        if (argc != REQUIRED_ARGC) {
            return ERROR;
        }

        Client client(argv[HOST_ARG], argv[PORT_ARG]);
        client.select_game_mode(atoi(argv[LOCAL_PLAYERS]));
        client.run();
        return SUCCESS;

    } catch (const std::exception& e) {
        std::cerr << "There was an exception in client main " << e.what() << std::endl;
        return ERROR;
    } catch (...) {
        std::cerr << "Unknown exception caught." << std::endl;
        return ERROR;
    }
} 