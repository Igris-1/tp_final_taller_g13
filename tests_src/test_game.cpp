#include <gtest/gtest.h>
#include "../server_src/game_model/game.h"
#include "../common_src/duck_DTO.h"

TEST(GameTest, GameCreation) {
    Game game(10,10);
    EXPECT_EQ(game.get_duck_DTO_list().size(), 0);
}

TEST(GameTest, GameId) {
    Game game(10,10);
    int id = game.add_duck(100, 0);
    EXPECT_EQ(id, 0);
    id = game.add_duck(2, 1);
    EXPECT_EQ(id, 1);
    id = game.add_duck(3, 2);
    EXPECT_EQ(id, 2);
    EXPECT_THROW(game.add_duck(3, 2), GameError);
}

TEST(GameTest, GameDucksetPositionAndMovement) {
    Game game(10,10);
    int id = game.add_duck(100, 1);
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
    int id = game.add_duck(100,1 );
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

TEST(GameTest, GameDuckDTO) {
    Game game(10,10);
    int id = game.add_duck(100,1 );
    game.set_duck_start_position(id, Position(0,0));
    
    game.move_duck(id, Position(1,0));
    Position pos = game.position_duck(id);

    std::vector<duck_DTO> list =  game.get_duck_DTO_list();
    EXPECT_EQ(list.size(), 1);

    EXPECT_EQ(list[0].duck_id, 1);
    EXPECT_EQ(list[0].x, pos.get_x());
    EXPECT_EQ(list[0].y, pos.get_y());
    EXPECT_EQ(list[0].running, false);

    game.add_duck(10, 2);
    game.set_duck_start_position(2, Position(5,5));
    game.run_duck(2, Position(1,0));
    game.continue_movements();
    list =  game.get_duck_DTO_list();
    EXPECT_EQ(list.size(), 2);

    EXPECT_EQ(list[0].duck_id, 1);
    EXPECT_EQ(list[0].x, 2);
    EXPECT_EQ(list[0].y, 0);
    EXPECT_EQ(list[0].running, false);


    EXPECT_EQ(list[1].duck_id, 2);
    EXPECT_EQ(list[1].x, 6);
    EXPECT_EQ(list[1].y, 5);
    EXPECT_EQ(list[1].running, true);
}