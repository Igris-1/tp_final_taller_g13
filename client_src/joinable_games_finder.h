#ifndef JOINABLE_GAMES_FINDER_H
#define JOINABLE_GAMES_FINDER_H

#include <vector>

#include "../common_src/DTOs.h"
#include "../common_src/socket.h"

class JoinableGamesFinder {
private:
    Socket socket;
    bool socket_is_closed = false;

public:
    JoinableGamesFinder(const char* host, const char* port);
    ~JoinableGamesFinder();
    void run();
    void stop();  // quizas no hace falta
    std::vector<games_DTO> ask_for_games();
};


#endif