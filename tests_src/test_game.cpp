#include <gtest/gtest.h>
#include "../server_src/game_model/game.h"

TEST(GameTest, GameCreation) {
    Game game(10,10);
    EXPECT_EQ(game.get_duck_DTO_list().size(), 0);
}

TEST(GameTest, GameId) {
    Game game(10,10);
    int id = game.add_duck(100);
    EXPECT_EQ(id, 0);
    id = game.add_duck(2);
    EXPECT_EQ(id, 1);
    id = game.add_duck(3);
    EXPECT_EQ(id, 2);
}

TEST(GameTest, GameDucksetPositionAndMovement) {
    Game game(10,10);
    int id = game.add_duck(100);
    game.set_duck_start_position(id, Position(0,0));
    Position pos = game.position_duck(id);

    EXPECT_EQ(pos, Position(0,0));

    game.move_duck(id, Position(1,0));
    pos = game.position_duck(id);
    EXPECT_EQ(pos, Position(1,0));

    game.move_duck(id, Position(0,1));
    pos = game.position_duck(id);
    EXPECT_EQ(pos, Position(1,1));

    game.move_duck(id, Position(1,-1));
    pos = game.position_duck(id);
    EXPECT_EQ(pos, Position(2,0));
}

TEST(GameTest, GameDuckRun) {
    Game game(10,10);
    int id = game.add_duck(100);
    game.set_duck_start_position(id, Position(0,0));
    
    game.run_duck(id, Position(1,0));
    Position pos = game.position_duck(id);
    EXPECT_EQ(pos, Position(0,0));

    game.continue_movements();
    pos = game.position_duck(id);
    EXPECT_EQ(pos, Position(1,0));

    game.continue_movements();
    pos = game.position_duck(id);
    EXPECT_EQ(pos, Position(2,0));

    game.stop_duck(id);
    game.continue_movements();
    pos = game.position_duck(id);
    EXPECT_EQ(pos, Position(2,0));

    game.continue_movements();
    game.continue_movements();
    game.continue_movements();
    pos = game.position_duck(id);
    EXPECT_EQ(pos, Position(2,0));
}