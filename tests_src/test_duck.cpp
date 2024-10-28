#include <gtest/gtest.h>

#include "../server_src/game_model/duck.h"

TEST(MathTest, duckLifeAndConstructor) {
        Duck duck(100, 1);
        EXPECT_TRUE(duck.is_alive());
        EXPECT_EQ(duck.get_health(), 100);
        EXPECT_EQ(duck.get_position().get_x(), -1);
        EXPECT_EQ(duck.get_position().get_y(), -1);
        EXPECT_TRUE(duck.is_this_duck(1)); // compara el id
        EXPECT_FALSE(duck.is_this_duck(2));

        duck.receive_damage(50);
        EXPECT_EQ(duck.get_health(), 50);
        EXPECT_TRUE(duck.is_alive());
        duck.receive_damage(50);
        EXPECT_FALSE(duck.is_alive());
}

// TEST(MathTest, duckMove) {
//         Duck duck(100, 1);
// }
