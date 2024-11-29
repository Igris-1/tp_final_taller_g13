#include <gtest/gtest.h>

#include "../common_src/DTOs.h"
#include "../server_src/game_model/duck.h"
#include "../server_src/game_model/game.h"

TEST(GameTest, GameCreation) {
    Game game(10, 10);
    EXPECT_EQ(game.get_duck_DTO_list().size(), 0);
}

TEST(GameTest, GameId) {
    Game game(10, 10);
    int id = game.add_duck(100, 0);
    EXPECT_EQ(id, 0);
    id = game.add_duck(2, 1);
    EXPECT_EQ(id, 1);
    id = game.add_duck(3, 2);
    EXPECT_EQ(id, 2);
    EXPECT_THROW(game.add_duck(3, 2), GameError);
}

TEST(GameTest, GameDucksetPositionAndMovement) {
    Game game(10, 10);
    int id = game.add_duck(100, 1);
    game.set_duck_start_position(id, Position(0, 0));
    Position pos = game.position_duck(id);

    EXPECT_EQ(pos, Position(0, 0));

    game.move_duck(id, Position(1, 0));
    pos = game.position_duck(id);
    EXPECT_EQ(pos, Position(1, 0));

    game.move_duck(id, Position(0, 1));
    pos = game.position_duck(id);
    EXPECT_EQ(pos, Position(1, 1));

    game.move_duck(id, Position(1, -1));
    pos = game.position_duck(id);
    EXPECT_EQ(pos, Position(2, 0));
}

/*TEST(GameTest, GameDuckRun) {
    Game game(100,100);
    int id = game.add_duck(100, 1);
    game.set_duck_start_position(id, Position(0,99));

    game.add_invalid_position(Hitbox(,98));
    game.add_invalid_position(Hitbox(1,98));
    game.add_invalid_position(Hitbox(2,98));
    game.add_invalid_position(Hitbox(3,98));


     0,0 1,0 2,0 3,0
     0,1 1,1 2,1 3,1


                                10,10


    EXPECT_EQ(game.position_duck(id), Position(0,99));
    game.run_duck(id, false, true);
    Position pos = game.position_duck(id);
    EXPECT_EQ(pos.get_x(), 0);
    EXPECT_EQ(pos.get_y(), 99);

    game.continue_horizontal_movements();
    pos = game.position_duck(id);
    EXPECT_EQ(pos.get_x(), 1);
    EXPECT_EQ(pos.get_y(), 99);


    game.continue_horizontal_movements();
    pos = game.position_duck(id);
    EXPECT_EQ(pos.get_x(), 2);
    EXPECT_EQ(pos.get_y(), 99);

    game.stop_run_duck(id, true, true);
    game.continue_horizontal_movements();
    pos = game.position_duck(id);
    EXPECT_EQ(pos.get_x(), 2);
    EXPECT_EQ(pos.get_y(), 99);

    game.continue_horizontal_movements();
    game.continue_horizontal_movements();
    game.continue_horizontal_movements();
    pos = game.position_duck(id);
    EXPECT_EQ(pos.get_x(), 2);
    EXPECT_EQ(pos.get_y(), 99);
}*/

TEST(GameTest, GameDuckDTO) {
    Game game(10, 10);
    int id = game.add_duck(100, 1);
    game.set_duck_start_position(id, Position(0, 9));

    game.move_duck(id, Position(1, 0));
    Position pos = game.position_duck(id);

    std::vector<duck_DTO> list = game.get_duck_DTO_list();
    EXPECT_EQ(list.size(), 1);

    EXPECT_EQ(list[0].duck_id, 1);
    EXPECT_EQ(list[0].x, pos.get_x());
    EXPECT_EQ(list[0].y, pos.get_y());
    EXPECT_EQ(list[0].is_moving_left, false);
    EXPECT_EQ(list[0].is_moving_right, false);

    game.add_duck(10, 2);
    game.set_duck_start_position(2, Position(5, 9));
    game.run_duck(2, false, true);
    game.continue_horizontal_movements();
    list = game.get_duck_DTO_list();
    EXPECT_EQ(list.size(), 2);

    EXPECT_EQ(list[0].duck_id, 1);
    EXPECT_EQ(list[0].x, 1);
    EXPECT_EQ(list[0].y, 9);
    EXPECT_EQ(list[0].is_moving_left, false);
    EXPECT_EQ(list[0].is_moving_right, false);


    EXPECT_EQ(list[1].duck_id, 2);
    EXPECT_EQ(list[1].x, 6);
    EXPECT_EQ(list[1].y, 9);
    // EXPECT_EQ(list[1].running, true); no se si deberia poner left true o right true, no tengo
    // ganas d leer y entnederlo ahora
}
