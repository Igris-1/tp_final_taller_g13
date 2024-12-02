#include <gtest/gtest.h>

#include "../server_src/protocol_server.h"
#include "../client_src/protocol_client.h"
#include "../common_src/socket.h"
#include "../common_src/liberror.h"

#define PORT_TEST 8081

Socket client("localhost", "8081");
Socket server ("localhost", "8081");

ProtocolClient protocol_client(std::move(client));
ProtocolServer protocol_server(std::move(server));

TEST(ProtocolTest, all) {
    std::cout << "aca" << std::endl;
}

// TEST(DuckTest, duckMove) {
//     Duck duck(100, 1);
//     duck.move_to(Position(1, 1));
//     EXPECT_EQ(duck.get_position(), Position(1, 1));

//     duck.move_relative_to(Position(1, 0));
//     EXPECT_EQ(duck.get_position(), Position(2, 1));

//     duck.move_relative_to(Position(0, -1));
//     EXPECT_EQ(duck.get_position(), Position(2, 0));

//     EXPECT_TRUE(duck.is_alive());

//     duck.move_to(Position(10, 10));
//     EXPECT_EQ(duck.get_position(), Position(10, 10));
// }

