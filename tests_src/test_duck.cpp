#include <gtest/gtest.h>

#include "../server_src/game_model/duck.h"
#include "../server_src/game_model/weapon/weapon.h"
#include "../server_src/game_model/armor.h"
#include "../server_src/game_model/helmet.h"


// TEST(DuckTest, duckLifeAndConstructor) {
//         Duck duck(100, 1);
//         EXPECT_TRUE(duck.is_alive());
//         EXPECT_EQ(duck.get_health(), 100);
//         EXPECT_EQ(duck.get_position().get_x(), -1);
//         EXPECT_EQ(duck.get_position().get_y(), -1);
//         EXPECT_TRUE(duck.is_this_duck(1)); // compara el id
//         EXPECT_FALSE(duck.is_this_duck(2));

//         duck.receive_damage(50);
//         EXPECT_EQ(duck.get_health(), 50);
//         EXPECT_TRUE(duck.is_alive());
//         duck.receive_damage(50);
//         EXPECT_FALSE(duck.is_alive());
// }

// TEST(DuckTest, duckMove) {
//         Duck duck(100, 1);
//         duck.move_to(Position(1,1));
//         EXPECT_EQ(duck.get_position(), Position(1,1));

//         duck.move_relative_to(Position(1,0));
//         EXPECT_EQ(duck.get_position(), Position(2,1));

//         duck.move_relative_to(Position(0,-1));
//         EXPECT_EQ(duck.get_position(), Position(2,0));

//         EXPECT_TRUE(duck.is_alive());

//         duck.move_to(Position(10,10));
//         EXPECT_EQ(duck.get_position(), Position(10,10));
// }

// TEST(DuckTest, duckItems) {
//         Duck duck(100, 1);
//         Weapon weapon(1);
//         Armor armor(1);
//         Helmet helmet(1);

//         duck.take_weapon(weapon);
//         duck.take_armor(armor);
//         duck.take_helmet(helmet);

//         duck.move_to(Position(1,1));
//         duck.throw_weapon_to(Position(2,1));

//         EXPECT_EQ(duck.get_weapon().get_position(), Position(2,1));     
// }
