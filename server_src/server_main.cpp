#include <iostream>

#include "server.h"

#define ERROR -1
#define SUCCESS 0
#define PORT_ARG 1
#define REQUIRED_ARGC 2


int main(int argc, char* argv[]) {
    try {
        if (argc != REQUIRED_ARGC) {
            std::cerr << "Error: invalid arguments" << std::endl;
            return ERROR;
        }
        Server server(argv[PORT_ARG]);
        server.start();
        return SUCCESS;

    } catch (const std::exception& e) {
        std::cerr << "There was an exception in server main " << e.what() << std::endl;
        return ERROR;
    } catch (...) {
        std::cerr << "Unknown exception caught." << std::endl;

        return ERROR;
    }
}